//STD Headers
#include <string>

//Library Headers

//Void Engine Headers
#include "Configurable.h"

namespace EngineUtils {
	Configurable::Configurable(
		const std::string& configFile, std::shared_ptr<ResourceManager> resourceManager) 
		: ConfigFilePath(std::move(configFile)), ResourceMngr(std::move(resourceManager)) {

		Config = nullptr;
		LoadConfiguration();
	}

	void Configurable::LoadConfiguration() {
		ResourceMngr->LoadResource<Configuration>(ConfigFilePath);
	}

	void Configurable::ReloadConfiguration() {
		ResourceMngr->ReloadResource<Configuration>(ConfigFilePath);
	}

	void Configurable::Reconfigure(const std::string& newConfigFilePath) {
		ResourceMngr->LoadResource<Configuration>(newConfigFilePath);
		ConfigFilePath = std::move(newConfigFilePath);
		Configure();
	}

}