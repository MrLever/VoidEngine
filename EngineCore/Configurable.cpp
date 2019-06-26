//STD Headers
#include <string>
#include "Configurable.h"

//Library Headers

//Coati Headers

namespace EngineCore {
	
	Configurable::Configurable(std::string configFileName) {
		LuaState = luaL_newstate();
		luaL_dofile(LuaState, configFileName.c_str());
		luaL_openlibs(LuaState);
		lua_pcall(LuaState, 0, 0, 0);

		ConfigTable = std::make_unique<luabridge::LuaRef*>(luabridge::getGlobal(LuaState, "testString"));
	}
}