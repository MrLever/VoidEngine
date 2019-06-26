#pragma once
//STD Headers
#include <string>

//Library Headers
#include "lua.hpp"
#include "LuaBridge\LuaBridge.h"

//Coati Headers

namespace EngineCore {

	class Configurable {
	private:
		//Private member variables
		lua_State* LuaState;
	protected:

	public:
		Configurable(std::string configFileName);

	};

}