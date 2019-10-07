//STD Headers

//Library Headers

//SuperVoid Headers
#include "BouncingCube.h"
#include "Logger.h"

namespace SuperVoid {
	BouncingCube::BouncingCube(const std::string& name) : Entity(name) {
		Velocity = 0.05f;
	}

	BouncingCube::BouncingCube(const utils::Name& name) : Entity(name) {
		Velocity = 0.05f;
	}
	
	void BouncingCube::BeginPlay() {
		utils::Logger::LogInfo(ID.StringID + " began play");
	}

	void SuperVoid::BouncingCube::Tick(float deltaSeconds) {
		Entity::Tick(deltaSeconds);

		auto deltaHeight = deltaSeconds * Velocity;
		auto deltaPitch = deltaSeconds * 1.0f;

		Position.Y += deltaHeight;
		Rotation.Pitch += deltaPitch;
		Rotation.Roll += deltaPitch;
		Rotation.Yaw += deltaPitch;

		if (Position.Y > 2 || Position.Y < -2) {
			Velocity *= -1;
		}
	}

	void BouncingCube::Terminate() {
	
	}
}