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

		luabridge::LuaRef s = luabridge::getGlobal(LuaState, "testString");
	}
}