#pragma once
//STD Headers
#include <atomic>
#include <concepts>
#include <filesystem>
#include <memory>
#include <unordered_map>

//Library Headers

//Void Engine Headers
#include "utils/Name.h"
#include "utils/Logger.h"
#include "utils/resource/Resource.h"
#include "utils/resource/ResourceHandle.h"
#include "utils/threading/ThreadPool.h"

namespace core {
	//Forward class declaration
	class Game;
}

namespace utils {

	class ResourceAllocatorBase {
		friend class core::Game;
	protected:
		/** 
		 * Optionally give all resource allocators acces to the thread pool
		 * for async resource loading
		 */
		static std::shared_ptr<ThreadPool> EngineThreadPool;
	};

	/**
	 * @class ResourceAllocator
	 * @brief A ResourceAllocator is responsible for managing the loading, caching 
	 *        and distribution of resources of type T
	 */
	template <class T>
	class ResourceAllocator : private ResourceAllocatorBase {
	public:
		/**
		 * Constructor
		 * @note This creates a synchronous ResourceAllocator
		 */
		ResourceAllocator();

		/**
		 * Destructor
		 */
		~ResourceAllocator();

		/**
		 * Instructs the allocator to load a resource from main memory
		 * @param filePath The location of the file
		 */
		ResourceHandle<T> LoadResource(const std::string& filePath);

		/**
		 * Instructs the allocator to load a resource from main memory
		 * even if it is currently cached
		 * @param filePath The location of the file
		 */
		ResourceHandle<T> ReloadResource(const std::string& filePath);

		/**
		 * Instructs the allocator to remove a cached resource
		 * @param filePath The location of the file
		 */
		void RemoveResource(const std::string& filePath);

		/**
		 * Instructs the allocator to aquire a cached resource
		 * @param fileID The ID of the file
		 */
		std::shared_ptr<T> GetResource(const Name& fileID);

	private:
		/** Registry of all loaded resources of this type */
		static std::unordered_map<Name, ResourceHandle<T>> m_ResourceCache;

		/** Mutex to synchronise access to the resource cache */
		std::recursive_mutex m_ResourceCacheLock;
	};

	template<class T>
	std::unordered_map<Name, ResourceHandle<T>> ResourceAllocator<T>::m_ResourceCache;

	template<class T>
	inline ResourceAllocator<T>::ResourceAllocator() {

	}

	template<class T>
	inline ResourceAllocator<T>::~ResourceAllocator() {

	}

	template<class T>
	inline ResourceHandle<T> ResourceAllocator<T>::LoadResource(const std::string& filePath) {
		//Check if resource loaded previously
		auto cacheIter = m_ResourceCache.find(utils::Name(filePath));
		if (cacheIter != m_ResourceCache.end()) {
			return cacheIter->second;
		}

		Name resourceIdentifier(filePath);

		if (!EngineThreadPool) {
			utils::Logger::LogError("ResourceAllocator cannot load resource " + filePath + ". No Thread Pool Available");
		}

		auto resourceFuture = EngineThreadPool->SubmitJob(
			[filePath, pool = EngineThreadPool]() -> std::shared_ptr<T> {
				std::shared_ptr<T> resource = std::make_shared<T>(filePath);
				if (!resource) {
					return nullptr;
				}

				if (resource->IsValid()) {
					resource->Load();
				}
				else {
					utils::Logger::LogWarning("Resource [" + filePath + "] not found. Loading default resource for this type");
					resource->LoadErrorResource();
				}

				return resource;
			}
		);

		ResourceHandle handle(resourceFuture);

		//Insert the new resource into the registry
		m_ResourceCache.insert({ resourceIdentifier, handle });
		return m_ResourceCache.find(resourceIdentifier)->second;
	}

	template<class T>
	inline ResourceHandle<T> ResourceAllocator<T>::ReloadResource(const std::string& filePath) {
		auto cacheIter = m_ResourceCache.find(filePath);
		if (cacheIter != m_ResourceCache.end()) {
			m_ResourceCache.erase(cacheIter->first);
		}

		return LoadResource(filePath);
	}

	template<class T>
	inline void ResourceAllocator<T>::RemoveResource(const std::string& filePath) {
		auto cacheIter = m_ResourceCache.find(filePath);

		if (cacheIter != m_ResourceCache.end()) {
			m_ResourceCache.erase(cacheIter->first);
		}
	}

	template<class T>
	inline std::shared_ptr<T> ResourceAllocator<T>::GetResource(const Name& fileID) {
		auto cacheIter = m_ResourceCache.find(fileID);

		if (cacheIter != m_ResourceCache.end()) {
			return cacheIter->second.GetResource();
		}
		else {
			return LoadResource(fileID.StringID).GetResource();
		}
	}
}

template <class T>
using ResourceAllocatorPtr = std::shared_ptr<utils::ResourceAllocator<T>>;

