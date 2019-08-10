#pragma once
//STD Headers
#include <filesystem>
#include <memory>
#include <unordered_map>

//Library Headers

//Void Engine Headers
#include "ResourceHandle.h"
#include "ThreadPool.h"
#include "Resource.h"
#include "UUID.h"

namespace EngineUtils {

	/**
	 * A resource manager is responsible for loading 
	 * and storing resources from main memory.
	 */
	class ResourceManager {
	public:
		///CTORS
		/**
		 * Constructor
		 * @param gameThreadPool A thread pool to be used for asynchronous file IO
		 */
		ResourceManager(std::shared_ptr<ThreadPool> gameThreadPool);
		
		/**
		 * Destructor
		 */
		~ResourceManager();

		///Public Member Functions
		/**
		 * A non-blocking function to command the resource manager to load a resource.
		 * If the resource has already been loaded, it will not be loaded again
		 * @param resourceLocation The resource's file location (which is translated to UUID)
		 */
		template <class T>
		void LoadResource(const std::string& resourceLocation);

		/**
		 * Non-blocking function to command the resource manager to reload a resource.
		 * If the resource has already been loaded, it *will*  reload from main memory update the resource registry accordingly
		 * @param resourceLocation The resource's file location (which is translated to UUID)
		 */
		template <class T> 
		void ReloadResource(const std::string& resourceLocation);

		/**
		 * Function to fetch a resource the caller thinks is already loaded.
		 * If it was not loaded, attempt to load it now
		 * @param resourceLocation The resources location on the hard drive
		 */
		template <class T>
		[[nodiscard]] std::shared_ptr<T> GetResource(const std::string& resourceLocation);

	private:
		///Private Member Variables
		/** The thread pool the Resource Manager depends on for async file IO */
		std::shared_ptr<ThreadPool> GameThreadPool;

		/** Registry of all loaded resources */
		std::unordered_map<UUID, ResourceHandle> ResourceRegistry;
	};

	template<class T>
	void ResourceManager::LoadResource(const std::string& resourceLocation) {
		auto RegistryEntry = ResourceRegistry.find(resourceLocation);

		//If the resource has been loaded abort the operation
		if (RegistryEntry != ResourceRegistry.end()) {
			return;
		}

		//Construct and allocate a resource on the heap
		auto resource = std::make_shared<T>(resourceLocation);
		std::future<bool> jobResult;

		if (!resource->GetResourceValid()) {
			//Submit the job to the threadpool and store a future to it's result.
			//Submitting the job as a lambda avoid expensive calls to std::bind
			jobResult = GameThreadPool->SubmitJob(
				[&]() { 
					return resource->LoadErrorResource(); 
				}
			);
		}
		else {
			//Submit the job to the threadpool and store a future to it's result.
			//Submitting the job as a lambda avoid expensive calls to std::bind
			jobResult = GameThreadPool->SubmitJob(
				[&]() { 
					return resource->Load(); 
				}
			);
		}

		ResourceHandle handle(resource, jobResult);

		//Insert the new resource into the registry
		ResourceRegistry.insert({ UUID(resourceLocation), handle });
	}
	
	template<class T>
	inline void ResourceManager::ReloadResource(const std::string& resourceLocation) {
		UUID resourceID = UUID(resourceLocation);
		auto RegistryEntry = ResourceRegistry.find(resourceID);

		//If the resource has not been loaded, load as normal
		if (RegistryEntry == ResourceRegistry.end()) {
			return LoadResource<T>(resourceLocation);
		}

		//Construct and allocate a resource on the heap
		auto resource = std::make_shared<T>(resourceLocation);
		std::future<bool> jobResult;

		if (!resource->GetResourceValid()) {
			//Submit the job to the threadpool and store a future to it's result.
			//Submitting the job as a lambda avoid expensive calls to std::bind
			jobResult = GameThreadPool->SubmitJob(
				[&]() {
					return resource->LoadErrorResource();
				}
			);
		}
		else {
			//Submit the job to the threadpool and store a future to it's result.
			//Submitting the job as a lambda avoid expensive calls to std::bind
			jobResult = GameThreadPool->SubmitJob(
				[&]() {
					return resource->Load();
				}
			);
		}

		ResourceHandle handle(resource, jobResult);

		//Insert the new resource into the registry
		RegistryEntry->second = std::move(handle);
	}
	template<class T>
	inline std::shared_ptr<T> ResourceManager::GetResource(const std::string& resourceLocation)
	{
		UUID resourceID(resourceLocation);

		if (ResourceRegistry.find(resourceID) == ResourceRegistry.end()) {
			LoadResource<T>(resourceLocation);
		}

		auto handle = ResourceRegistry.find(resourceID)->second;
		return handle.GetResource<T>();
	}

}

