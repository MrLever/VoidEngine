//STD Headers
#include <string>

//Library Headers

//Void Engine Headers
#include "Configurable.h"

namespace EngineUtils {
	Configurable::Configurable(
		const std::string& name, const std::string& configFile, std::shared_ptr<ResourceManager> resourceManager) 
		: ID(std::move(name)), ConfigFilePath(std::move(configFile)), ResourceMngr(std::move(resourceManager)) {

		Config = nullptr;
	}

	std::strong_ordering Configurable::operator<=>(const Configurable& other) const {
		return ID <=> other.ID;
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

	UUID Configurable::GetUUID() {
		return ID;
	}
}