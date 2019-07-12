#pragma once
//STD Headers
#include <memory>
#include <unordered_set>

//Library Headers

//Void Engine Headers
#include "ThreadPool.h"

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
	
	private:
		///Private Member Variables
		std::shared_ptr<ThreadPool> GameThreadPool;
	};
}

