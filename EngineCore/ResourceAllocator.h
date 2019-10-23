#pragma once
//STD Headers
#include <atomic>
#include <concepts>
#include <filesystem>
#include <memory>
#include <unordered_map>

//Library Headers

//Void Engine Headers
#include "ResourceHandle.h"
#include "ThreadPool.h"
#include "Resource.h"
#include "Name.h"
#include "Logger.h"

namespace utils {

	/**
	 * @class ResourceAllocator
	 * @brief A ResourceAllocator is responsible for managing the loading, caching 
	 *        and distribution of resources of type T
	 */
	template <class T>
	class ResourceAllocator {
	public:
		/**
		 * Constructor
		 * @param gameThreadPool A thread pool to be used for asynchronous file IO
		 */
		ResourceAllocator(ThreadPoolPtr gameThreadPool);
		
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
		 * @param filePath The location of the file
		 */
		std::shared_ptr<T> GetResource(const std::string& filePath);

		/**
		 * Instructs the allocator to aquire a cached resource
		 * @param fileID The ID of the file
		 */
		std::shared_ptr<T> GetResource(const Name& fileID);


	private:
		/** The thread pool the Resource Manager depends on for async file IO */
		std::shared_ptr<ThreadPool> GameThreadPool;

		/** Registry of all loaded resources */
		std::unordered_map<Name, ResourceHandle<T>> ResourceCache;

		/** Mutex to synchronise access to the Resource Manager */
		std::recursive_mutex ResourceManagerLock;
	};

	template<class T>
	inline ResourceAllocator<T>::ResourceAllocator(ThreadPoolPtr gameThreadPool) 
		: GameThreadPool(std::move(gameThreadPool)){
	
	}

	template<class T>
	inline ResourceAllocator<T>::~ResourceAllocator() {
	}

	template<class T>
	inline ResourceHandle<T> ResourceAllocator<T>::LoadResource(const std::string& filePath) {
		//Check if resource loaded previously
		auto cacheIter = ResourceCache.find(utils::Name(filePath));
		if (cacheIter != ResourceCache.end()) {
			return cacheIter->second;
		}

		Name resourceIdentifier(filePath);

		ThreadPoolPtr pool = GameThreadPool;

		auto resourceFuture = GameThreadPool->SubmitJob(
			[filePath, pool]() -> std::shared_ptr<T> {
				std::shared_ptr<T> resource = std::make_shared<T>(filePath);
				if (!resource) {
					return nullptr;
				}

				if (resource->IsValid()) {
					if (resource->GetIsComposite()) {
						resource->AttatchThreadPool(pool);
					}
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
		ResourceCache.insert({ resourceIdentifier, handle });
		return ResourceCache.find(resourceIdentifier)->second;
	}

	template<class T>
	inline ResourceHandle<T> ResourceAllocator<T>::ReloadResource(const std::string& filePath) {
		auto cacheIter = ResourceCache.find(filePath);
		if (cacheIter != ResourceCache.end()) {
			ResourceCache.erase(cacheIter->first);
		}

		return LoadResource(filePath);
	}

	template<class T>
	inline void ResourceAllocator<T>::RemoveResource(const std::string& filePath) {
		auto cacheIter = ResourceCache.find(filePath);

		if (cacheIter != ResourceCache.end()) {
			ResourceCache.erase(cacheIter->first);
		}
	}

	template<class T>
	inline std::shared_ptr<T> ResourceAllocator<T>::GetResource(const std::string& filePath) {
		return GetResource(Name(filePath));
	}

	template<class T>
	inline std::shared_ptr<T> ResourceAllocator<T>::GetResource(const Name& fileID) {
		auto cacheIter = ResourceCache.find(fileID);

		if (cacheIter != ResourceCache.end()) {
			return cacheIter->second.GetResource();
		}
		else {
			return LoadResource(fileID.StringID).GetResource();
		}
	}
}

template <class T>
using ResourceAllocatorPtr = std::shared_ptr<utils::ResourceAllocator<T>>;

