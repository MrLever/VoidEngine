//STD Headers
#include <string>

//Library Headers

//Void Engine Headers
#include "Configurable.h"

namespace EngineUtils {
	Configurable::Configurable(std::string configFile) : ID(std::move(configFile)) {
	
	}
	Configurable::Configurable(std::string configFile, std::string name) : ID(std::move(name)) {
	}

	std::strong_ordering Configurable::operator<=>(const Configurable& other) const {
		return ID <=> other.ID;
	}
}