//STD Headers
#include <iostream>
#include <string>

//Library Headers

//Coati Headers
#include "EngineCore/Game.h"

using namespace core;

int main(int argc, char* argv[]) {
	std::string config = "Settings/EngineConfig.json";

	if (argc > 1) {
		config = std::string(argv[1]);
	}

	Game game(config);

	return 0;
}

