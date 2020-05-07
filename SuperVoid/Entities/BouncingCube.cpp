//STD Headers

//Library Headers

//SuperVoid Headers
#include "utils/Logger.h"

#include "BouncingCube.h"

namespace SuperVoid {

	ENABLE_FACTORY(BouncingCube, core::Entity)

	BouncingCube::BouncingCube() {
		Velocity = 0.05f;
	}
	
	void BouncingCube::Initialize() {
		Entity::Initialize();
	}

	void BouncingCube::BeginPlay() {
		utils::Logger::LogInfo(name.StringID + " began play");
	}

	void SuperVoid::BouncingCube::Tick(float deltaSeconds) {
		Entity::Tick(deltaSeconds);

		auto deltaHeight = deltaSeconds * Velocity;
		math::Quaternion deltaRotation(math::Rotator(-1, 1, -1));

		transform.position.Y += deltaHeight;

		transform.rotation *= deltaRotation;

		if (transform.position.Y > 2 || transform.position.Y < -2) {
			Velocity *= -1;
		}
	}

	void BouncingCube::Terminate() {
	
	}
}