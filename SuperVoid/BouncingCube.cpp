//STD Headers

//Library Headers

//SuperVoid Headers
#include "utils/Logger.h"

#include "BouncingCube.h"

namespace SuperVoid {

	TYPE_INFO_IMPL(BouncingCube)

	ENABLE_FACTORY(BouncingCube, core::Entity)

	BouncingCube::BouncingCube() {
		Velocity = 0.05f;
	}
	
	void BouncingCube::Initialize() {
		Entity::Initialize();
	}

	void BouncingCube::BeginPlay() {
		utils::Logger::LogInfo(m_Name.StringID + " began play");
	}

	void SuperVoid::BouncingCube::Tick(float deltaSeconds) {
		Entity::Tick(deltaSeconds);

		auto deltaHeight = deltaSeconds * Velocity;
		math::Quaternion deltaRotation(math::Rotator(-1, 1, -1));

		auto position = m_Transform.GetPosition();
		position.Y += deltaHeight;

		auto rotation = m_Transform.GetRotation();
		rotation = rotation * deltaRotation;

		if (position.Y > 2 || position.Y < -2) {
			Velocity *= -1;
		}

		m_Transform.SetPosition(position);
		m_Transform.SetRotation(rotation);
	}

	void BouncingCube::Terminate() {
	
	}
}