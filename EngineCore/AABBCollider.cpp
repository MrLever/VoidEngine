//STD Headers

//Library Headers

//Void Engine Headers
#include "AABBCollider.h"
#include "SphereCollider.h"
#include "Logger.h"

namespace core {

	bool AABBCollider::Collide(AABBCollider* other) {
		utils::Logger::LogInfo("Narrow-Phase Collision handling: AABB - AABB");
		return false;
	}

	bool AABBCollider::Collide(SphereCollider* other) {
		utils::Logger::LogInfo("Narrow-Phase Collision handling: AABB - Sphere");
		return false;
	}

}
