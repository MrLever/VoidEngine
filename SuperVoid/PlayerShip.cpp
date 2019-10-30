//STD Headers

//Library Headers

//Void Engine Headers
#include "PlayerShip.h"

namespace SuperVoid {
	PlayerShip::PlayerShip(const utils::Name& name) : PlayerEntity(name) {

	}

	PlayerShip::PlayerShip(const std::string& name) : PlayerEntity(name) {

	}

	void PlayerShip::Initialize() {
		;
	}

	void PlayerShip::SetupInputComponent(core::InputComponent* component) {
		;
	}
}