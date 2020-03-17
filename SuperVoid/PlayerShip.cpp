//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/factory/Factory.h"
#include "PlayerShip.h"

namespace SuperVoid {

	TYPE_INFO_IMPL(PlayerShip)

	ENABLE_FACTORY(PlayerShip, core::Entity)

	PlayerShip::PlayerShip() : m_RigidBody(nullptr) {
		
	}

	void PlayerShip::Initialize() {
		Entity::Initialize();

		m_RigidBody = GetComponent<core::PhysicsComponent>();
	}

	void PlayerShip::SetupInputComponent(core::InputComponent* component) {
		component->BindAxis(
			"MoveForward",
			[this](float axisReading, float deltaTime) {
				MoveForward(axisReading, deltaTime);
			}
		);

		component->BindAxis(
			"MoveRight",
			[this](float axisReading, float deltaTime) {
				MoveRight(axisReading, deltaTime);
			}
		);
	}

	void PlayerShip::MoveForward(float axisValue, float deltaTime) {
		m_RigidBody->ApplyForce(math::Vector3(0, axisValue * deltaTime, 0));
	}
	
	void PlayerShip::MoveRight(float axisValue, float deltaTime) {
		m_RigidBody->ApplyForce(math::Vector3(axisValue * deltaTime, 0, 0));
	}
}