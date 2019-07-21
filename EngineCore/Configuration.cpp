#pragma once
//STD Headers


//Library Headers
#include "lua.hpp"
#include "LuaBridge\LuaBridge.h"

//Void Engine Headers
#include "Configuration.h"

namespace EngineUtils {
	
	///CTORS
	Configuration::Configuration(std::string configFile) : Resource(configFile) {
		LuaState = luaL_newstate();
	}

	Configuration::~Configuration() {
	}

	///Public Member Functions
	bool Configuration::Load() {
		return false;
	}

	bool Configuration::LoadErrorResource() {
		return false;
	}
}