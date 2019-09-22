//STD Headers
#include <iostream>

//Library Headers

//Void Engine Headers
#include "PlayerEntity.h"

namespace EngineCore {
	void PlayerEntity::BeginPlay() {
		std::cout << "Player Entity Online";
	}

	void PlayerEntity::Tick(float deltaSeconds) {

	}

	void PlayerEntity::Terminate() {

	}
}