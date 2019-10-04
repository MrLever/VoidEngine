//STD Headers

//Library Headers

//Void Engine Headers
#include "ResourceManager.h"

namespace utils {
	///Public Functions
	ResourceManager::ResourceManager(ThreadPoolPtr gameThreadPool) 
		: GameThreadPool(std::move(gameThreadPool)) {
	
	}

	ResourceManager::~ResourceManager() {
	
	}

}