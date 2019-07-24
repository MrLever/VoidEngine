#pragma once
//STD Headers
#include <limits>
#include <memory>
#include <string>

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
		///Private Member Functions
		/**
		 * Helper function for returning an error value if a key is not found in a config file
		 * @return defualt error value for type T
		 */
		template<typename T>
		T ReturnErrorValue();

		/**
		 * Logic to load Configuration Table into ConfigTable
		 */
		void LoadConfigTable();

		///Private Member Variables

		inline static const std::string ErrorScript = "Settings = { Error = true }";

		/** The Lua State associated with this configuration script */
		lua_State* LuaState;
		std::unique_ptr<luabridge::LuaRef> ConfigTable;
	};

	template<typename T>
	inline T Configuration::GetAttribute(std::string attribute) {
		//auto configTable = luabridge::getGlobal(LuaState, "Settings");
		luabridge::LuaRef result = (*ConfigTable)[attribute];
		
		if (result.isNil()) {
			std::cerr << "ERROR: Attribute " << attribute << "not found in LuaConfiguration";
			return ReturnErrorValue<T>();
		}

		return result.cast<T>();
	}

	template<typename T>
	inline T Configuration::ReturnErrorValue(){
		if (std::numeric_limits<T>::is_specialized) {
			return std::numeric_limits<T>::max();
		}
		else {
			return T();
		}
	}
}
