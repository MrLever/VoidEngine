#pragma once
//STD Headers
#include <string>
#include <memory>

//Library Headers

//Void Engine Headers
#include "utils/configuration/Configurable.h"

namespace utils {
	
	Configuration::Configuration(const std::string& configFile) : JsonResource(configFile) {

	}

	Configuration::~Configuration() {

	}

}