//STD Headers
#include <iostream>
#include <string>

//Library Headers

//Void Engine Headers
#include "core/Game.h"

using namespace core;

int main(int argc, char* argv[]) {
	std::string config = (argc > 1) ? std::string(argv[1]) : "Settings/EngineConfig.json";

	Game game(config);

	return 0;
}

