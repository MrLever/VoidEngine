//STD headers

//Library Headers

//Void Engine Headers
#include "ConfigManager.h"
#include "ResourceManager.h"

namespace EngineUtils {
	ConfigManager::ConfigManager(std::shared_ptr<ResourceManager> resourceManager) 
		: GameResourceManager(std::move(resourceManager)){

	}

	void ConfigManager::RegisterConfigurable(Configurable* user) {
		
	}
}