//STD Headers

//Library Headers

//Void Engine Headers
#include "PlayerShip.h"
#include "Factory.h"

namespace SuperVoid {

	ENABLE_FACTORY(PlayerShip, core::Entity)

	PlayerShip::PlayerShip() {

	}

	void PlayerShip::Initialize() {
		Entity::Initialize();
	}

	void PlayerShip::SetupInputComponent(core::InputComponent* component) {
		;
	}
}