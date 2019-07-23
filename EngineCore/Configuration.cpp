#pragma once
//STD Headers
#include <string>
#include <memory>

//Library Headers
#include "lua.hpp"
#include "LuaBridge\LuaBridge.h"

//Void Engine Headers
#include "Configuration.h"

namespace EngineUtils {
	
	///CTORS
	Configuration::Configuration(std::string configFile) : Resource(configFile) {
		//Create the Lua state
		LuaState = luaL_newstate();
		ConfigTable = std::make_unique<luabridge::LuaRef>(LuaState);
	}

	Configuration::~Configuration() {
		lua_close(LuaState);
	}

	///Public Member Functions
	bool Configuration::Load() {
		
		//Open our Lua script
		int loadFlag = luaL_loadfile(LuaState, ResourcePath.string().c_str());

		//Load the standard Lua Libraries into the lua state
		luaL_openlibs(LuaState);

		//Call the script loaded in the LuaState
		int pcallFlag = lua_pcall(LuaState, 0, 0, 0);

		if (loadFlag || pcallFlag) {
			std::cerr << "Error: Lua script failed to load";
			return false;
		}

		//Load the configuration table from the script
		/*ConfigTable = std::make_unique<luabridge::LuaRef>(
			luabridge::getGlobal(LuaState, "Settings")
		);*/
		
		


		return true;
	}

	bool Configuration::LoadErrorResource() {
		return false;
	}
}