#pragma once
//STD Headers
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
		std::mutex ResourceManagerLock;
	};

	using ResourceManagerPtr = std::shared_ptr<EngineUtils::ResourceManager>;

	template<class T>
	ResourceHandle ResourceManager::LoadResource(const std::string& resourceLocation) {
		std::scoped_lock<std::mutex> lock(ResourceManagerLock);

		auto RegistryEntry = ResourceRegistry.find(resourceLocation);

		//If the resource has been loaded abort the operation
		if (RegistryEntry != ResourceRegistry.end()) {
			return RegistryEntry->second;
		}

		//Construct and allocate a resource on the heap
		auto resource = std::make_shared<T>(resourceLocation);
		std::future<bool> jobResult;

		if (!resource->GetResourceValid()) {
			//Submit the job to the threadpool and store a future to it's result.
			//Submitting the job as a lambda avoid expensive calls to std::bind
			jobResult = GameThreadPool->SubmitJob(
				[resource]() {
					return resource->LoadErrorResource(); 
				}
			);
		}
		else {
			//Submit the job to the threadpool and store a future to it's result.
			//Submitting the job as a lambda avoid expensive calls to std::bind
			jobResult = GameThreadPool->SubmitJob(
				[resource]() {
					return resource->Load();
				}
			);
		}

		Name resourceName(resourceLocation);
		ResourceHandle handle(resource, jobResult);

		//Insert the new resource into the registry
		ResourceRegistry.insert({ resourceName, handle });
		return ResourceRegistry.find(resourceName)->second;
	}
	
	template<class T>
	inline ResourceHandle ResourceManager::ReloadResource(const std::string& resourceLocation) {
		std::scoped_lock<std::mutex> lock(ResourceManagerLock);

		Name resourceName = Name(resourceLocation);
		auto RegistryEntry = ResourceRegistry.find(resourceName);

		//If the resource has not been loaded, load as normal
		if (RegistryEntry == ResourceRegistry.end()) {
			return LoadResource<T>(resourceLocation);
		}
		else {
			ResourceRegistry.erase(resourceName);
		}

		//Construct and allocate a resource on the heap
		auto resource = std::make_shared<T>(resourceLocation);
		std::future<bool> jobResult;

		if (!resource->GetResourceValid()) {
			//Submit the job to the threadpool and store a future to it's result.
			//Submitting the job as a lambda avoid expensive calls to std::bind
			jobResult = GameThreadPool->SubmitJob(
				[resource]() {
					return resource->LoadErrorResource();
				}
			);
		}
		else {
			//Submit the job to the threadpool and store a future to it's result.
			//Submitting the job as a lambda avoid expensive calls to std::bind
			jobResult = GameThreadPool->SubmitJob(
				[resource]() {
					return resource->Load();
				}
			);
		}

		ResourceHandle handle(resource, jobResult);
		RegistryEntry->second = std::move(handle);
		
		return ResourceRegistry.find(resourceName)->second;
	}
	
	template<class T>
	inline ResourceHandle ResourceManager::GetResource(const std::string& resourceLocation) {
		std::scoped_lock<std::mutex> lock(ResourceManagerLock);
		Name resourceName(resourceLocation);

		if (ResourceRegistry.find(resourceName) == ResourceRegistry.end()) {
			return LoadResource<T>(resourceLocation);
		}

		auto handle = ResourceRegistry.find(resourceName)->second;
		return handle;
	}

}

