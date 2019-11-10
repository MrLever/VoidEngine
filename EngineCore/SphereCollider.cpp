//STD Headers

//Library Headers

//Void Engine Headers
#include "SphereCollider.h"
#include "AABBCollider.h"
#include "Factory.h"
#include "Logger.h"

namespace core {

	ENABLE_FACTORY(SphereCollider, Collider)

	SphereCollider::SphereCollider() : Radius(1.0) {

	}

	SphereCollider::SphereCollider(float r) : Radius(r) {

	}

	bool SphereCollider::DetectCollision(AABBCollider* other) {
		utils::Logger::LogInfo("Narrow-Phase Collision handling: Sphere - AABB");
		return false;
	}

	bool SphereCollider::DetectCollision(SphereCollider* other) {
		utils::Logger::LogInfo("Narrow-Phase Collision handling: Sphere - Sphere");
		return false;
	}

	float SphereCollider::GetRadius() {
		return Radius;
	}

}