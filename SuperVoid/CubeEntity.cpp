//STD Headers
#include <cmath>
#include <iostream>

//Engine Headers
#include "Shader.h"
#include "TimeUtils.h"

//SuperVoid Headers
#include "CubeEntity.h"

namespace SuperVoid {
	CubeEntity::CubeEntity(const std::string& name) : Entity(name) {
		Velocity = 0.05f;
	}

	CubeEntity::~CubeEntity() {

	}

	void CubeEntity::BeginPlay() {
		std::cout << ID.StringID << " began play\n";
	}

	void CubeEntity::Tick(float deltaSeconds) {
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
	
	void CubeEntity::Terminate() {

	}
}