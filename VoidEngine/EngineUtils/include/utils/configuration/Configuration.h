#pragma once
//STD Headers
#include <limits>
#include <memory>
#include <string>

//Library Headers


//Void Engine Headers
#include "utils/resource/JsonResource.h"

namespace utils {
	class Configuration : public JsonResource {
	public:
		/**
		 * Constructor
		 * @param configFile the resource's filepath
		 */
		Configuration(const std::string& configFile);

		/**
		 * Destructor
		 */
		~Configuration();

	};
}
