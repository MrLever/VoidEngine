#pragma once
//STD Headers
#include <memory>
#include <compare>

//Library Headers

//Void Engine Headers
#include "UUID.h"

namespace EngineUtils {
	
	/**
	 * Configurable is an abstract base class that allows subclasses to interact with a configuration manager
	 */
	class Configurable {
	public:
		Configurable(std::string configFile);
		Configurable(std::string configFile, std::string name);

		virtual void Configure() = 0;

		std::strong_ordering operator<=>(const Configurable& other) const;

	protected:

	private:
		UUID ID;
	};
}