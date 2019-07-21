#pragma once
//STD Headers
#include <string>
#include <memory>

//Library Headers
#include "lua.hpp"
#include "LuaBridge\LuaBridge.h"

//Void Engine Headers
#include "Resource.h"

namespace EngineUtils {
	class Configuration : Resource {
	public:
		///CTORS
		/**
		 * Constructor
		 * @param configFile the resource's filepath
		 */
		Configuration(std::string configFile);

		/**
		 * Destructor
		 * Cleans up the LuaState to guard against memory leaks
		 */
		~Configuration();

		///Public Member Functions
		/**
		 * Loads a lua configuration script from main memory
		 * @return whether the load was successful. 
		 */
		bool Load() override;

		/**
		 * Loads a default lua configuration if the provided resource was inacessable
		 * @return whether the load was successful.
		 */
		bool LoadErrorResource() override;

	private:
		/** The Lua State associated with this configuration script */
		lua_State* LuaState;
	};
}
