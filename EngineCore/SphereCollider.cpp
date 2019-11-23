//STD Headers
#include <algorithm>

//Library Headers

//Void Engine Headers
#include "SphereCollider.h"

namespace core {

	ENABLE_FACTORY(SphereCollider, Collider)

	bool SphereCollider::CallbacksRegistered = false;

	SphereCollider::SphereCollider() : Radius(0.0f) {
		if (!CallbacksRegistered) {
			ColliderComponent::RegisterCollisionDetectionCallback<SphereCollider, SphereCollider>(DetectSphereCollision);
		}
	}

	void SphereCollider::Initialize() {
		Radius = ShapeData["radius"].get<float>();
	}

	float SphereCollider::GetRadius() {
		return Radius;
	}

	Manifold* SphereCollider::DetectSphereCollision(ColliderComponent* left, ColliderComponent* right) {
		const SphereCollider* sphere1 = reinterpret_cast<const SphereCollider*>(left->GetShape());
		const SphereCollider* sphere2 = reinterpret_cast<const SphereCollider*>(left->GetShape());

		auto collisionDistance = sphere1->Radius + sphere2->Radius;
		auto collisionDistanceSquared = collisionDistance * collisionDistance;
		
		auto distanceSquared = left->GetDistanceSquared(right);
		
		//Early termination
		if (distanceSquared > collisionDistanceSquared) {
			return nullptr;
		}

		utils::Logger::LogDebug("Sphere vs Sphere Collision Detected");

		auto distance = left->GetDistance(right);

		// This pointer must be freed by the physics engine after the collision is resolved.
		Manifold* collision = new Manifold();
		collision->ColliderA = left;
		collision->ColliderB = right;

		//Get direction vector between colliders
		math::Vector3 translationVector = right->GetPosition() - left->GetPosition();

		if (translationVector.Magnitude2() < COLLISION_EPSILON) {
			//Special case for overlapping spheres
			collision->PenetrationDistance = sphere1->Radius;
			collision->CollisionNormal = math::Vector3(0, 1, 0);
		}
		else {
			//Normal manifold generation
			collision->PenetrationDistance = collisionDistance - distance;
			collision->CollisionNormal = translationVector.Normalize();
		}

		return collision;
	}

	void SphereCollider::ResolveSphereCollision(Manifold* collision) {
		auto colliderA = collision->ColliderA;
		auto objectA = colliderA->GetParent();
		auto bodyA = objectA->GetBody();

		auto colliderB = collision->ColliderB;
		auto objectB = colliderB->GetParent();
		auto bodyB = objectB->GetBody();

		float restitution = std::min(bodyA->Restitution, bodyB->Restitution);
		auto relativeVelocity = bodyB->Velocity - bodyA->Velocity;
		auto relVelocityAlongNormal = relativeVelocity.Dot(collision->CollisionNormal);

		if (relVelocityAlongNormal > 0) {
			//If the relative velocity is positive, the objects are separating
			return;
		}

		//Calculate impulse
		float impulse = -(1 + restitution) * relVelocityAlongNormal;
		impulse /= (bodyA->InverseMass) + (1 / bodyB->InverseMass);

		//Apply impulses, but not to static objects
		auto impulseVector = impulse * collision->CollisionNormal;
		if (bodyA->PhysicsEnabled) {
			bodyA->Velocity -= (bodyA->InverseMass) * impulseVector;
		}
		if (bodyB->PhysicsEnabled) {
			bodyB->Velocity += (1 / bodyB->InverseMass) * impulseVector;
		}

	}

	utils::Name SphereCollider::GetTypename() const {
		return utils::Name("SphereCollider");
	}

	utils::Name SphereCollider::GetStaticTypename() {
		return utils::Name("SphereCollider");
	}

}