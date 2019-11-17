//STD Headers

//Library Headers

//Void Engine Headers
#include "SphereCollider.h"

namespace core {
	ENABLE_FACTORY(SphereCollider, Collider)

	bool SphereCollider::CallbacksRegistered = false;

	SphereCollider::SphereCollider() : Radius(0.0f) {
		if (!CallbacksRegistered) {
			ColliderComponent::RegisterCollisionCallback<SphereCollider, SphereCollider>(DetectSphereCollision);
		}
	}

	void SphereCollider::Initialize() {
		Radius = ShapeData["radius"].get<float>();
	}

	float SphereCollider::GetRadius() {
		return Radius;
	}

	bool SphereCollider::DetectSphereCollision(Collider* left, Collider* right) {
		return false;
	}

}