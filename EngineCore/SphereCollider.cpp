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

	bool SphereCollider::DetectSphereCollision(ColliderComponent* left, ColliderComponent* right) {
		const SphereCollider* sphere1 = reinterpret_cast<const SphereCollider*>(left->GetShape());
		const SphereCollider* sphere2 = reinterpret_cast<const SphereCollider*>(left->GetShape());

		auto collisionDistance = sphere1->Radius + sphere2->Radius;
		auto collisionDistanceSquared = collisionDistance * collisionDistance;
		
		auto distanceSquared = left->GetDistanceSquared(right);
		return distanceSquared <= collisionDistanceSquared;
	}

	utils::Name SphereCollider::GetTypename() const {
		return utils::Name("SphereCollider");
	}

	utils::Name SphereCollider::GetStaticTypename() {
		return utils::Name("SphereCollider");
	}

}