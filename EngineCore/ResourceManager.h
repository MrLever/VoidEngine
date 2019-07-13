#pragma once
//STD Headers
#include <filesystem>
#include <memory>
#include <unordered_map>

//Library Headers

//Void Engine Headers
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
		template <typename P>
		using ResourceHandle = std::future<std::shared_ptr<P>>;
		
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
		 */
		/*template <typename T> 
		ResourceHandle<T> LoadResource(std::filesystem::path resourceLocation);*/

	
	private:
		///Private Member Variables
		/** The thread pool the Resource Manager depends on for async file IO */
		std::shared_ptr<ThreadPool> GameThreadPool;

		/** Registry of all loaded resources */
		std::unordered_map<UUID, Resource> ResourceRegistry;
	};

	//template<typename T>
	//inline ResourceManager::ResourceHandle<T> ResourceManager::LoadResource(std::filesystem::path resourceLocation) {
	//	return ResourceHandle<T>();
	//}
}

