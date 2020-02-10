//STD Headers
#include <string>

//Library Headers

//Void Engine Headers
#include "utils/configuration/Configurable.h"

namespace utils {
	Configurable::Configurable(const  ResourceHandle<Configuration>& configuration)
		: Config(std::move(configuration)) {

	}

	void Configurable::Reconfigure(ResourceHandle<Configuration> newResource) {
		Config = newResource;
		Configure();
	}
}