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

		/**
		 * Function for retrieving values from a Lua Config file
		 * @tparam T The expected type of the attribute
		 * @param attribute The requested attribute's key
		 * @return The requested attribute
		 */
		template<typename T>
		T GetAttribute(std::string attribute);

	private:
		/** The Lua State associated with this configuration script */
		lua_State* LuaState;
		std::unique_ptr<luabridge::LuaRef> ConfigTable;
	};

	template<typename T>
	inline T Configuration::GetAttribute(std::string attribute) {
		luabridge::LuaRef result = (*ConfigTable)[attribute];
		
		return result.cast<T>();
	}
}
