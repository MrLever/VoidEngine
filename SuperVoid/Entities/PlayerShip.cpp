//STD Headers

//Library Headers

//Void Engine Headers
#include "core/Scene.h"
#include "utils/factory/Factory.h"
#include "PlayerShip.h"

namespace SuperVoid {

	TYPE_INFO_IMPL(PlayerShip)

	ENABLE_FACTORY(PlayerShip, core::Entity)

	PlayerShip::PlayerShip() : m_EngineStrength(10), m_RigidBody(nullptr), m_BulletPrototype({}) {

	}

	void PlayerShip::Initialize() {
		Entity::Initialize();

		m_RigidBody = GetComponent<core::PhysicsComponent>();
		SetupInputComponent(GetComponent<core::InputComponent>());

		if (configData.find("speed") != configData.end()) {
			m_EngineStrength = configData["speed"];
		}

		m_BulletPrototype = core::Prototype(configData["bulletPrototype"]);
	}

	void PlayerShip::SetupInputComponent(core::InputComponent* component) {
		component->BindAxis(
			"MoveUp",
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

		component->BindAxis(
			"Rotate",
			[this](float axisReading, float deltaTime) {
				Rotate(axisReading, deltaTime);
			}
		);

		component->BindAction(
			"Fire",
			core::ActionType::PRESSED,
			[this](float deltaTime) {
				Fire();
			}
		);
	}

	void PlayerShip::Tick(float deltaTime) {
		core::PlayerEntity::Tick(deltaTime);
		if (std::abs(transform.position.X) > 75) {
			transform.position.X *= -1;
		}

		if (std::abs(transform.position.Y) > 75) {
			transform.position.Y *= -1;
		}

	}
	
	void PlayerShip::MoveForward(float axisValue, float deltaTime) {
		m_RigidBody->ApplyForce(math::Vector3(0, m_EngineStrength * axisValue * deltaTime, 0));
	}
	
	void PlayerShip::MoveRight(float axisValue, float deltaTime) {
		m_RigidBody->ApplyForce(math::Vector3(m_EngineStrength * axisValue * deltaTime, 0, 0));
	}

	void PlayerShip::Rotate(float axisValue, float deltaTime) {
		math::Rotator deltaRotation(0, 0, -axisValue * deltaTime * 500);

		transform.rotation = deltaRotation * transform.rotation;
	}

	void PlayerShip::Fire() {
		auto bullet = GetWorld()->SpawnEntity(m_BulletPrototype);
		bullet->SetPosition(GetPosition() + GetForward() * 3);
		bullet->SetRotation(GetRotation());
		bullet->GetComponent<core::PhysicsComponent>()->AddVelocity(
			GetComponent<core::PhysicsComponent>()->GetVelocity()
		);
	}
}