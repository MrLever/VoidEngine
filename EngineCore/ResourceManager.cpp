//STD Headers

//Library Headers

//Void Engine Headers
#include "ResourceManager.h"

namespace EngineUtils {
	///Public Functions
	ResourceManager::ResourceManager(std::shared_ptr<ThreadPool> gameThreadPool) : GameThreadPool(std::move(gameThreadPool)) {
	
	}

	ResourceManager::~ResourceManager() {
	
	}

	void ResourceManager::GarbageCollect() {

	}

}