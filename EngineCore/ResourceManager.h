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
		void LoadResource(const std::string& resourceLocation);

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
		UUID resourceID = UUID(resourceLocation);
		auto RegistryEntry = ResourceRegistry.find(resourceID);

		//If the resource has been loaded, 
		//return a resource handle with the resource already loaded
		if (RegistryEntry != ResourceRegistry.end()) {
			return;
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

