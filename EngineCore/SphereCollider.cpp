//STD Headers

//Library Headers

//Void Engine Headers
#include "SphereCollider.h"
#include "AABBCollider.h"

namespace core {
	SphereCollider::SphereCollider() : Radius(1.0) {

	}

	SphereCollider::SphereCollider(float r) : Radius(r) {

	}

	bool SphereCollider::Collide(AABBCollider* other) {
		utils::Logger::LogInfo("Narrow-Phase Collision handling: Sphere - AABB");
		return false;
	}

	bool SphereCollider::Collide(SphereCollider* other) {
		utils::Logger::LogInfo("Narrow-Phase Collision handling: Sphere - Sphere");
		return false;
	}

	float SphereCollider::GetRadius() {
		return Radius;
	}

}