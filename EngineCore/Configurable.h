#pragma once
//STD Headers
#include <string>
#include <memory>

//Library Headers
#include "lua.hpp"
#include "LuaBridge\LuaBridge.h"

//Coati Headers

namespace EngineCore {

	class Configurable {
	private:
		//Private member variables
		lua_State* LuaState;
		std::unique_ptr<luabridge::LuaRef*> ConfigTable;

		std::string configFile;

	protected:
		virtual void Configure() = 0;

		template<typename T>
		T GetAttribute(std::string attribute);

	public:
		Configurable(std::string configFileName);

	};

	template<typename T>
	inline T Configurable::GetAttribute(std::string attribute)
	{
		luabridge::LuaRef result = ConfigTable[attribute.c_str()];
		return result.cast<T>();
	}

}