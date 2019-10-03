#pragma once
//STD Headers
#include <string>
#include <memory>

//Library Headers

//Void Engine Headers
#include "Configuration.h"

namespace EngineUtils {
	
	Configuration::Configuration(const std::string& configFile) : Resource(configFile) {

	}

	Configuration::~Configuration() {

	}

	bool Configuration::Load() {
		
		std::ifstream configFile(ResourcePath);

		if (!configFile.is_open()) {
			return LoadErrorResource();
		}

		configFile >> ConfigData;
		return true;
	}

	bool Configuration::LoadErrorResource() {
		ConfigData["Error"] = true;

		return true;
	}

	void Configuration::Initialize() {
	
	}
}