//STD Headers
#include <string>

//Library Headers

//Void Engine Headers
#include "Configurable.h"

namespace EngineUtils {
	Configurable::Configurable(
			std::string name, 
			std::string configFile, 
			std::shared_ptr<ResourceManager> resourceManager
		) : ID(std::move(name)), ConfigFilePath(configFile), ResourceMngr(resourceManager) {

		Config = nullptr;
	}

	std::strong_ordering Configurable::operator<=>(const Configurable& other) const {
		return ID <=> other.ID;
	}

	void Configurable::LoadConfiguration() {
		ResourceMngr->LoadResource<Configuration>(ConfigFilePath);
	}
}