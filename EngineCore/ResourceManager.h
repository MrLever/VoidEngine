#pragma once
//STD Headers
#include <atomic>
#include <filesystem>
#include <memory>
#include <unordered_map>
#include <iostream>

//Library Headers

//Void Engine Headers
#include "ResourceHandle.h"
#include "ThreadPool.h"
#include "Resource.h"
#include "Name.h"

namespace EngineUtils {

	/**
	 * A resource manager is responsible for loading 
	 * and storing resources from main memory.
	 */
	class ResourceManager {
	public:
		/**
		 * Constructor
		 * @param gameThreadPool A thread pool to be used for asynchronous file IO
		 */
		ResourceManager(std::shared_ptr<ThreadPool> gameThreadPool);
		
		/**
		 * Destructor
		 */
		~ResourceManager();

		/**
		 * A non-blocking function to command the resource manager to load a resource.
		 * If the resource has already been loaded, it will not be loaded again
		 * @param resourceLocation The resource's file location (which is translated to Name)
		 */
		template <class T>
		ResourceHandle LoadResource(const std::string& resourceLocation);

		/**
		 * Non-blocking function to command the resource manager to reload a resource.
		 * If the resource has already been loaded, it *will*  reload from main memory update the resource registry accordingly
		 * @param resourceLocation The resource's file location (which is translated to Name)
		 */
		template <class T> 
		ResourceHandle ReloadResource(const std::string& resourceLocation);

		/**
		 * Function to fetch a resource the caller thinks is already loaded.
		 * If it was not loaded, attempt to load it now
		 * @param resourceLocation The resources location on the hard drive
		 */
		template <class T>
		[[nodiscard]] ResourceHandle GetResource(const std::string& resourceLocation);

	private:
		/** The thread pool the Resource Manager depends on for async file IO */
		std::shared_ptr<ThreadPool> GameThreadPool;

		/** Registry of all loaded resources */
		std::unordered_map<Name, ResourceHandle> ResourceRegistry;

		/** Mutex to synchronise access to the Resource Manager */
		std::recursive_mutex ResourceManagerLock;
	};

	template<class T>
	ResourceHandle ResourceManager::LoadResource(const std::string& resourceLocation) {
		std::scoped_lock<std::recursive_mutex> lock(ResourceManagerLock);

		auto RegistryEntry = ResourceRegistry.find(resourceLocation);

		//If the resource has been loaded abort the operation
		if (RegistryEntry != ResourceRegistry.end()) {
			return RegistryEntry->second;
		}

		Name resourceName(resourceLocation);

		auto resourceFuture = GameThreadPool->SubmitJob(
			[resourceLocation]() -> std::shared_ptr<Resource> {
				std::shared_ptr<Resource> resource = std::make_shared<T>(resourceLocation);
				if (!resource) {
					return nullptr;
				}

				if (resource->GetResourceValid()) {
					resource->Load();
				}
				else {
					resource->LoadErrorResource();
				}

				return resource;
			}
		);

		ResourceHandle handle(resourceFuture);

		//Insert the new resource into the registry
		ResourceRegistry.insert({ resourceName, handle });
		return ResourceRegistry.find(resourceName)->second;
	}
	
	template<class T>
	inline ResourceHandle ResourceManager::ReloadResource(const std::string& resourceLocation) {
		std::scoped_lock<std::recursive_mutex> lock(ResourceManagerLock);

		auto RegistryEntry = ResourceRegistry.find(resourceLocation);
		if (RegistryEntry == ResourceRegistry.end()) {
			return LoadResource<T>(resourceLocation);
		}
		else {
			auto handle = RegistryEntry->second;

			//Block until previous load is completed.
			handle.RequestedResource.wait();

			//Erase entry from map
			ResourceRegistry.erase(RegistryEntry);
			return LoadResource<T>(resourceLocation);
		}
	}
	
	template<class T>
	inline ResourceHandle ResourceManager::GetResource(const std::string& resourceLocation) {
		std::scoped_lock<std::recursive_mutex> lock(ResourceManagerLock);
		Name resourceName(resourceLocation);

		auto RegistryEntry = ResourceRegistry.find(resourceName);

		if ( RegistryEntry == ResourceRegistry.end()) {
			return LoadResource<T>(resourceLocation);
		}

		return RegistryEntry->second;
	}

}

using ResourceManagerPtr = std::shared_ptr<EngineUtils::ResourceManager>;

