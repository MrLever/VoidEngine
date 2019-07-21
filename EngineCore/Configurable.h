#pragma once
//STD Headers
#include <string>
#include <memory>

//Library Headers
#include "lua.hpp"
#include "LuaBridge\LuaBridge.h"

//Void Engine Headers

namespace EngineCore {

	class Configurable {
	private:
		//Private member variables
		lua_State* LuaState;
		luabridge::LuaRef ConfigTable;

		std::string ConfigFilePath;

	public:
		//ctors
		Configurable(std::string configFileName);
		~Configurable();
	protected:
		virtual void Configure() = 0;

		template<typename T>
		T GetAttribute(std::string attribute);

		void ReloadConfigurationFile();
		void LoadNewConfigurationFile(std::string newConfigFile);

	private:
		//Private member functions
		void LoadConfigurationFile();
		
	};

	template<typename T>
	inline T Configurable::GetAttribute(std::string attribute) {
		luabridge::LuaRef result = ConfigTable[attribute];
		
		return result.cast<T>();
	}

}