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
	}

	Configuration::~Configuration() {
		ConfigTable.reset();
		lua_close(LuaState);
	}

	void Configuration::LoadConfigTable() {
		ConfigTable = std::make_unique<luabridge::LuaRef>(
			luabridge::getGlobal(LuaState, "Settings")
			);
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
			LoadErrorResource();
			LoadConfigTable();
			return false;
		}

		LoadConfigTable();

		return true;
	}

	bool Configuration::LoadErrorResource() {
		luaL_loadstring(LuaState, ErrorScript.c_str());
		
		//Load the standard Lua Libraries into the lua state
		luaL_openlibs(LuaState);

		//Call the script loaded in the LuaState
		int pcallFlag = lua_pcall(LuaState, 0, 0, 0);

		return true;
	}
}