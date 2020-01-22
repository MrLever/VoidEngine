//STD Headers

//Library Headers

//Void Engine Headers
#include "EngineCore/Factory.h"
#include "PlayerShip.h"

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