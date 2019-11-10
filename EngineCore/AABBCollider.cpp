//STD Headers

//Library Headers

//Void Engine Headers
#include "AABBCollider.h"
#include "SphereCollider.h"
#include "Factory.h"
#include "Logger.h"

namespace core {

	ENABLE_FACTORY(AABBCollider, Collider)

	bool AABBCollider::DetectCollision(AABBCollider* other) {
		utils::Logger::LogInfo("Narrow-Phase Collision handling: AABB - AABB");
		return false;
	}

	bool AABBCollider::DetectCollision(SphereCollider* other) {
		utils::Logger::LogInfo("Narrow-Phase Collision handling: AABB - Sphere");
		return false;
	}

}
