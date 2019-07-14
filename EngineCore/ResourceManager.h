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
		 * Function to command the resource manager to load a resource.
		 * If the resource has already been loaded, it will not be loaded again
		 * @param resourceLocation The resource's file location (which is translated to UUID)
		 * @return A thread safe handle to the requested resource
		 */
		template <class T>
		ResourceHandle LoadResource(const std::string& resourceLocation);

	private:
		///Private Member Variables
		/** The thread pool the Resource Manager depends on for async file IO */
		std::shared_ptr<ThreadPool> GameThreadPool;

		/** Registry of all loaded resources */
		std::unordered_map<UUID, ResourceHandle> ResourceRegistry;
	};

	template<class T>
	ResourceHandle ResourceManager::LoadResource(const std::string& resourceLocation) {
		UUID resourceID = UUID(resourceLocation);
		auto RegistryEntry = ResourceRegistry.find(resourceID);

		//If the resource has been loaded, 
		//return a resource handle with the resource already loaded
		if (RegistryEntry != ResourceRegistry.end()) {
			return RegistryEntry->second;
		}

		//Construct the resource handle
		auto resource = std::make_shared<T>(resourceLocation);
		std::future<bool> jobResult;

		if (!resource->GetResourceValid()) {
			jobResult = GameThreadPool->SubmitJob(std::bind(&T::LoadErrorResource, resource.get()));
		}
		else {
			jobResult = GameThreadPool->SubmitJob(std::bind(&T::Load, resource.get()));
		}

		ResourceHandle handle(resource, jobResult);

		//Insert the new resource into the registry
		ResourceRegistry.insert({ resourceID, handle });

		//Return the resource handle
		return handle;
	}
}

