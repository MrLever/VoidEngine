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
		 */
		template <class T>
		ResourceHandle LoadResource(const std::string& resourceLocation);
	
		/**
		 * Iterates through the resourceRegistry and removes all unused assets
		 */
		void GarbageCollect();

	private:
		///Private Member Variables
		/** The thread pool the Resource Manager depends on for async file IO */
		std::shared_ptr<ThreadPool> GameThreadPool;

		/** Registry of all loaded resources */
		std::unordered_map<UUID, std::shared_ptr<Resource>> ResourceRegistry;
	};

	template<class T>
	ResourceHandle ResourceManager::LoadResource(const std::string& resourceLocation) {
		UUID resourceID = UUID(resourceLocation);
		auto RegistryEntry = ResourceRegistry.find(resourceID);

		//If the resource has been loaded, 
		//return a resource handle with the resource already loaded
		if (RegistryEntry != ResourceRegistry.end()) {
			std::promise<bool> resourcePromise;

			resourcePromise.set_value(
				RegistryEntry->second->GetLoadComplete()
			);

			std::shared_ptr<Resource> resource = RegistryEntry->second;

			return ResourceHandle(resource, resourcePromise);
		}

		auto resource = std::make_shared<T>(resourceLocation);

		/*return ResourceHandle(
			resource,
			GameThreadPool->SubmitJob(
				std::bind(resource->Load)
			);
		);*/
	}
}

