//STD Headers
#include <string>

//Library Headers

//Coati Headers
#include "Configurable.h"

namespace EngineCore {
	/**
	 * Constructor
	 * Loads configuration file from hard drive
	 */
	Configurable::Configurable(std::string configFileName) 
		: ConfigFilePath(configFileName), LuaState(luaL_newstate()), ConfigTable(LuaState) {
		
		//Open standard lua libs
		//luaL_openlibs(LuaState);

		//Reset config table
		//ConfigTable(LuaState);

		//LoadConfigurationFile();
	}

	Configurable::~Configurable(){
		if (LuaState) {
			//lua_close(LuaState);
		}
	}

	/**
	 * Reloads the configuration file from the hard drive
	 */
	void Configurable::ReloadConfigurationFile() {
		LoadConfigurationFile();
		Configure();
	}

	/**
	 * Loads a new configuration file from the hard drive
	 * @param newConfigFile Path to the new configuration file
	 */
	void Configurable::LoadNewConfigurationFile(std::string newConfigFile) {
		ConfigFilePath = newConfigFile;
		LoadConfigurationFile();
		Configure();
	}

	/**
	 * Private function to load a lua file into memory
	 */
	void Configurable::LoadConfigurationFile() {
		int res = luaL_loadfile(LuaState, ConfigFilePath.c_str());
		if (res) {
			std::cout << res << "\n";
			std::cerr << "ERROR LOADING LUA FILE";
		}

		lua_pcall(LuaState, 0, 0, 0);
		luabridge::LuaRef tablename = luabridge::getGlobal(LuaState, "tablename");
		if (tablename.isNil()) {
			std::cerr << "ERROR: Configurable cannot find tablename";
			return;
		}



		ConfigTable = luabridge::getGlobal(LuaState, tablename);
		
		/*if (ConfigTable.isNil()) {
			std::cerr << "FUCKING SHITT";
		}*/
		
		//std::cout << luaString << std::endl;
	}
}