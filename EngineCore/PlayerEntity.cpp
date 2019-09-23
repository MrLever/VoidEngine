//STD Headers
#include <iostream>

//Library Headers

//Void Engine Headers
#include "PlayerEntity.h"

namespace EngineCore {
	PlayerEntity::PlayerEntity(const std::string& name) : Entity(name) {

	}

	void PlayerEntity::BeginPlay() {
		std::cout << "Player Entity Online\n";
	}

	void PlayerEntity::Tick(float deltaSeconds) {

	}

	void PlayerEntity::Terminate() {

	}
}