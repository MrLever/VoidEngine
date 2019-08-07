#pragma once
//STD Headers
#include <memory>

//Library Headers

//Void Engine Headers

namespace EngineCore {
	
	/**
	 * Configurable is an abstract base class that allows subclasses to interact with a configuration manager
	 */
	class Configurable {
	public:
		Configurable(std::string configFile);
	protected:

	private:
	
	};
}