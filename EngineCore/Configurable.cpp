//STD Headers
#include <string>

//Library Headers

//Void Engine Headers
#include "Configurable.h"

namespace utils {
	Configurable::Configurable(const ResourceHandle& configuration) 
		: Config(std::move(configuration)) {

	}

	void Configurable::Reconfigure(ResourceHandle newResource) {
		Config = newResource;
		Configure();
	}
}