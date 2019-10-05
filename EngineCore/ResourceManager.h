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
	 * @class ResourceManager
	 * @brief A ResourceManager is responsible for managing the loading 
	 *        and distribution of resources of type T
	 */
	template <class T>
	class ResourceManager {
	public:
		/**
		 * Constructor
		 * @param gameThreadPool A thread pool to be used for asynchronous file IO
		 */
		ResourceManager(ThreadPoolPtr gameThreadPool);
		
		/**
		 * Destructor
		 */
		~ResourceManager();

		ResourceHandle<T> LoadResource(const std::string& filePath);

		ResourceHandle<T> ReloadResource(const std::string& filePath);

		void RemoveResource(const std::string& filePath);

		std::shared_ptr<T> GetResource(const std::string& filePath);

		std::shared_ptr<T> GetResource(const Name& filePath);


	private:
		/** The thread pool the Resource Manager depends on for async file IO */
		std::shared_ptr<ThreadPool> GameThreadPool;

		/** Registry of all loaded resources */
		std::unordered_map<Name, ResourceHandle<T>> ResourceCache;

		/** Mutex to synchronise access to the Resource Manager */
		std::recursive_mutex ResourceManagerLock;
	};

	template<class T>
	inline ResourceManager<T>::ResourceManager(ThreadPoolPtr gameThreadPool) 
		: GameThreadPool(std::move(gameThreadPool)){
	
	}

	template<class T>
	inline ResourceManager<T>::~ResourceManager() {
	}

	template<class T>
	inline ResourceHandle<T> ResourceManager<T>::LoadResource(const std::string& filePath) {
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
					resource->Load();
				}
				else {
					resource->LoadErrorResource();
				}

				if (resource->GetIsComposite()) {
					resource->AttatchThreadPool(pool);
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
	inline ResourceHandle<T> ResourceManager<T>::ReloadResource(const std::string& filePath) {
		auto cacheIter = ResourceCache.find(filePath);
		if (cacheIter != ResourceCache.end()) {
			ResourceCache.erase(cacheIter->first);
		}

		return LoadResource(filePath);
	}

	template<class T>
	inline void ResourceManager<T>::RemoveResource(const std::string& filePath) {
		auto cacheIter = ResourceCache.find(filePath);

		if (cacheIter != ResourceCache.end()) {
			ResourceCache.erase(cacheIter->first);
		}
	}

	template<class T>
	inline std::shared_ptr<T> ResourceManager<T>::GetResource(const std::string& filePath) {
		return GetResource(Name(filePath));
	}

	template<class T>
	inline std::shared_ptr<T> ResourceManager<T>::GetResource(const Name& filePath) {
		auto cacheIter = ResourceCache.find(filePath);

		if (cacheIter != ResourceCache.end()) {
			return cacheIter->second.GetResource();
		}
		else {
			return LoadResource(filePath.StringID).GetResource();
		}
	}
}

template <class T>
using ResourceManagerPtr = std::shared_ptr<utils::ResourceManager<T>>;

