//STD Headers

//Library Headers

//Void Headers
#include "MainMenu.h"

namespace SuperVoid {
	
	MainMenu::MainMenu() {
		Entities.emplace_back(std::make_shared<CubeEntity>("TestCubeEntitiy"));
	}

	MainMenu::~MainMenu() {
	}

}