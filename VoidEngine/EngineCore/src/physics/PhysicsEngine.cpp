//STD Headers

//Library Headers

//Void Engine Headers
#include "physics/PhysicsEngine.h"
#include "physics/components/PhysicsComponent.h"
#include "physics/components/ColliderComponent.h"
#include "physics/colliders/SphereCollider.h"
#include "physics/colliders/AABBCollider.h"

namespace core {

	// Static variable initialization
	const float PhysicsEngine::COLLISION_EPSILON = 0.0001f;

	PhysicsEngine::PhysicsEngine(
		EventSystem* eventSystem, 
		const utils::ResourceHandle<utils::Configuration>& configuration
	) : EventListener(eventSystem), Configurable(configuration), Gravity(9.8f) {
		utils::Logger::LogInfo("Initializing Physics Engine Collision System");
		ColliderComponent::RegisterCollisionDetectionCallback<SphereCollider, SphereCollider>(DetectSphereSphereCollision);
		ColliderComponent::RegisterCollisionDetectionCallback<AABBCollider, AABBCollider>(DetectAABBAABBCollision);
		ColliderComponent::RegisterCollisionDetectionCallback<SphereCollider, AABBCollider>(DetectSphereAABBCollision);
		ColliderComponent::RegisterCollisionDetectionCallback<AABBCollider, SphereCollider>(DetectAABBSphereCollision);
	}
	
	void PhysicsEngine::Configure() {
		;
	}

	void PhysicsEngine::SetGravity(float gravity) {
		Gravity = gravity;
	}
	
	void PhysicsEngine::Simulate(const std::vector<std::unique_ptr<Entity>>& entities, float deltaTime) {
		//Physics simulations update 60 times per second
		static float accumulator = 0.0f;
		static const float PHYSICS_DT = 0.016f; 

		std::vector<PhysicsComponent*> physicsComponents;
		for (auto& entity : entities) {
			auto body = entity->GetComponent<PhysicsComponent>();
			if (body) {
				physicsComponents.push_back(body);
			}
		}

		std::vector<ColliderComponent*> colliders;
		for (auto& entity : entities) {
			auto collider = entity->GetComponent<ColliderComponent>();
			if (collider) {
				colliders.push_back(collider);
			}
		}

		accumulator += deltaTime;

		while (accumulator >= PHYSICS_DT) {
			ApplyForces(physicsComponents, PHYSICS_DT);
			Integrate(physicsComponents, PHYSICS_DT);
			HandleCollisions(colliders, PHYSICS_DT);

			accumulator -= PHYSICS_DT;
		}

		//Apply the remainder 
		/*if (accumulator != 0) {
			ApplyForces(physicsComponents, accumulator);
			Integrate(physicsComponents, accumulator);
			HandleCollisions(colliders, accumulator);
			accumulator = 0;
		}*/
	}

	void PhysicsEngine::ApplyForces(std::vector<PhysicsComponent*>& physicsComponents, float deltaTime) {
		//apply gravity
		for (auto& body : physicsComponents) {		
			auto force = body->GetMass() * Gravity * math::Vector3(0, -1, 0);
			force *= body->GetGravityScale();

			body->ApplyForce(force);
		}
	}

	void PhysicsEngine::Integrate(std::vector<PhysicsComponent*>& physicsComponents, float deltaTime) {
		//Resolve forces
		for (auto& body : physicsComponents) {
			auto parent = body->GetParent();

			auto x_i = parent->GetPosition();
			auto a = (body->GetForce() * body->GetInverseMass());

			body->AddVelocity(a * deltaTime);

			auto x_f = x_i + (body->GetVelocity() * deltaTime);

			parent->SetPosition(x_f);

			//Clear active forces after resolved
			body->ClearForce();
		}
	}

	void PhysicsEngine::HandleCollisions(std::vector<ColliderComponent*>& colliders, float deltaTime) {
		auto manifolds = DetectCollisions(colliders);
		ResolveCollisions(manifolds);

		// Destroy manifolds to prevent memory leak
		for (auto& manifold : manifolds) {
			delete manifold;
		}
	}

	std::unordered_set<Manifold*> PhysicsEngine::DetectCollisions(std::vector<ColliderComponent*>& colliders) {
		std::unordered_set<Manifold*> manifolds;
		//O(n^2) Collision detection
		for (int i = 0; i < colliders.size(); i++) {
			for (int j = i+1; j < colliders.size(); j++) {
				
				if (colliders[i]->GetCollisionLayer() == colliders[j]->GetCollisionLayer()) {
					continue;
				}

				auto manifold = colliders[i]->DetectCollision(colliders[j]);
				if (manifold) {
					manifolds.insert(manifold);
				}
			}
		}

		return manifolds;
	}

	void PhysicsEngine::ResolveCollisions(std::unordered_set<Manifold*>& collisions) {
		for (auto& manifold : collisions) {
			manifold->EntityA->OnHit();
			manifold->EntityB->OnHit();
			ResolveCollision(manifold);
			CorrectPositions(manifold);
		}
	}

	void PhysicsEngine::ResolveCollision(Manifold* collision) {
		auto objectA = collision->EntityA;
		auto bodyA = objectA->GetComponent<PhysicsComponent>();

		auto objectB = collision->EntityB;
		auto bodyB = objectB->GetComponent<PhysicsComponent>();

		if (bodyA == nullptr && bodyB == nullptr) {
			return;
		}

		//Calculate bounciness of collision
		float resA = (bodyA == nullptr) ? 1 : bodyA->GetRestitution();
		float resB = (bodyB == nullptr) ? 1 : bodyB->GetRestitution();
		float restitution = std::min(resA, resB);

		//Calculate relative velocity of collision
		math::Vector3 velocityA = (bodyA == nullptr) ? math::Vector3() : bodyA->GetVelocity();
		math::Vector3 velocityB = (bodyB == nullptr) ? math::Vector3() : bodyB->GetVelocity();
		auto relativeVelocity = velocityB - velocityA;
		auto relVelocityAlongNormal = relativeVelocity.Dot(collision->CollisionNormal);

		if (relVelocityAlongNormal > 0) {
			//If the relative velocity is positive, the objects are separating
			return;
		}

		//Gather object masses
		float invMassA = (bodyA == nullptr) ? 0 : bodyA->GetInverseMass();
		float invMassB = (bodyB == nullptr) ? 0 : bodyB->GetInverseMass();

		//Calculate impulse magnitude
		float impulse = -(1 + restitution) * relVelocityAlongNormal;
		impulse /= (invMassA + invMassB);

		//Apply impulses, but not to static objects
		auto impulseVector = impulse * collision->CollisionNormal;
		if (bodyA != nullptr && !bodyA->GetIsStatic()) {
			bodyA->AddVelocity(-(invMassA * impulseVector));
		}
		if (bodyB != nullptr && !bodyB->GetIsStatic()) {
			bodyB->AddVelocity(invMassB * impulseVector);
		}
	}

	void PhysicsEngine::CorrectPositions(Manifold* collision) {
		const float MAX_PEN = 0.01f;
		const float CORRECTION_FACTOR = 0.2f;

		//Ignore small errors
		if (collision->PenetrationDistance < MAX_PEN) {
			return;
		}

		auto objectA = collision->EntityA;
		auto bodyA = objectA->GetComponent<PhysicsComponent>();

		auto objectB = collision->EntityB;
		auto bodyB = objectB->GetComponent<PhysicsComponent>();

		//Gather object masses
		float invMassA = (bodyA == nullptr) ? 0 : bodyA->GetInverseMass();
		float invMassB = (bodyB == nullptr) ? 0 : bodyB->GetInverseMass();

		float correctionConstant = collision->PenetrationDistance / (invMassA + invMassB);
		correctionConstant *= CORRECTION_FACTOR;
		math::Vector3 correctionVector = correctionConstant * collision->CollisionNormal;

		if (bodyA && !bodyA->GetIsStatic()) {
			//Scale positional correction by mass of object
			objectA->SetPosition(objectA->GetPosition() - correctionVector * invMassA);
		}
		if (bodyB && !bodyB->GetIsStatic()) {
			//Scale positional correction by mass of object
			objectB->SetPosition(objectB->GetPosition() + correctionVector * invMassB);
		}
	}

	Manifold* PhysicsEngine::DetectSphereSphereCollision(ColliderComponent* left, ColliderComponent* right) {
		const SphereCollider* sphere1 = reinterpret_cast<const SphereCollider*>(left->GetShape());
		const SphereCollider* sphere2 = reinterpret_cast<const SphereCollider*>(right->GetShape());

		auto collisionDistance = sphere1->GetRadius() + sphere2->GetRadius();
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
		collision->EntityA = left->GetParent();
		collision->EntityB = right->GetParent();

		//Get direction vector between colliders
		math::Vector3 translationVector = right->GetPosition() - left->GetPosition();

		if (translationVector.MagnitudeSqr() < COLLISION_EPSILON) {
			//Special case for overlapping spheres
			collision->PenetrationDistance = sphere1->GetRadius();
			collision->CollisionNormal = math::Vector3(0, 1, 0);
		}
		else {
			//Normal manifold generation
			collision->PenetrationDistance = collisionDistance - distance;
			collision->CollisionNormal = translationVector.Normalize();
		}

		return collision;
	}

	Manifold* PhysicsEngine::DetectAABBAABBCollision(ColliderComponent* left, ColliderComponent* right) {
		const AABBCollider* aabb1 = reinterpret_cast<const AABBCollider*>(left->GetShape());
		const AABBCollider* aabb2 = reinterpret_cast<const AABBCollider*>(right->GetShape());

		auto aabb1Pos = left->GetPosition();
		auto aabb2Pos = right->GetPosition();

		auto translationVector = aabb2Pos - aabb1Pos;

		//SAT- Project onto x axis
		float xWidth1 = (aabb1->GetMax().X - aabb1->GetMin().X) / 2;
		float xWidth2 = (aabb1->GetMax().X - aabb1->GetMin().X) / 2;

		float xOverlap = xWidth1 + xWidth2 - std::abs(translationVector.X);
		if (xOverlap < 0) {
			//X axis is separating axis
			return nullptr;
		}

		//SAT- Project onto y axis
		float yWidth1 = (aabb1->GetMax().Y - aabb1->GetMin().Y) / 2;
		float yWidth2 = (aabb1->GetMax().Y - aabb1->GetMin().Y) / 2;

		float yOverlap = yWidth1 + yWidth2 - std::abs(translationVector.Y);
		if (yOverlap < 0) {
			//Y axis is separating axis
			return nullptr;
		}

		//SAT- Project onto z axis
		float zWidth1 = (aabb1->GetMax().Z - aabb1->GetMin().Z) / 2;
		float zWidth2 = (aabb1->GetMax().Z - aabb1->GetMin().Z) / 2;

		float zOverlap = zWidth1 + zWidth2 - std::abs(translationVector.Z);
		if (zOverlap < 0) {
			//Z axis is separating axis
			return nullptr;
		}

		//No separating axis found
		auto manifold = new Manifold();
		manifold->EntityA = left->GetParent();
		manifold->EntityB = right->GetParent();

		//At this point it is certain there is no separating axis, the objects are colliding
		//Find smallest axis of seperation
		if (xOverlap < yOverlap && yOverlap <= zOverlap) {
			manifold->PenetrationDistance = xOverlap;
			auto xAxis = math::Vector3(1, 0, 0);
			if (translationVector.X < 0) {
				xAxis *= -1;
			}
			manifold->CollisionNormal = xAxis;
		}
		else if (yOverlap <= zOverlap && zOverlap <= xOverlap) {
			//Allow for equal in this case to default to resolving collisions upward
			manifold->PenetrationDistance = yOverlap;
			auto yAxis = math::Vector3(0, 1, 0);
			if (translationVector.Y < 0) {
				yAxis *= -1;
			}
			manifold->CollisionNormal = yAxis;
		}
		else if (zOverlap < xOverlap && xOverlap <= yOverlap) {
			manifold->PenetrationDistance = zOverlap;
			auto zAxis = math::Vector3(0, 0, 1);
			if (translationVector.Z < 0) {
				zAxis *= -1;
			}
			manifold->CollisionNormal = zAxis;
		}

		return manifold;
	}

	Manifold* PhysicsEngine::DetectSphereAABBCollision(ColliderComponent* left, ColliderComponent* right) {
		const SphereCollider* sphere = reinterpret_cast<const SphereCollider*>(left->GetShape());
		const AABBCollider* aabb = reinterpret_cast<const AABBCollider*>(right->GetShape());

		//Calculate relevant AABB info
		auto aabbPos = right->GetPosition();
		auto aabbMin = aabb->GetMin() + aabbPos;
		auto aabbMax = aabb->GetMax() + aabbPos;

		//Get translation vector to calculate point of interest
		auto translationVector = right->GetPosition() - left->GetPosition();

		//Clamping used instead of projections because box is axis-aligned
		auto poiX = std::max(aabbMin.X, std::min(aabbMax.X, aabbPos.X - translationVector.X));
		auto poiY = std::max(aabbMin.Y, std::min(aabbMax.Y, aabbPos.Y - translationVector.Y));
		auto poiZ = std::max(aabbMin.Z, std::min(aabbMax.Z, aabbPos.Z - translationVector.Z));

		//Closest point on any face of the AABB to the sphere
		math::Vector3 POI(poiX, poiY, poiZ);

		auto translationVectorPrime = POI - left->GetPosition();
		if (translationVectorPrime.MagnitudeSqr() > sphere->GetRadius() * sphere->GetRadius()) {
			return nullptr;
		}

		Manifold* collision = new Manifold();
		collision->EntityA = left->GetParent();
		collision->EntityB = right->GetParent();
		collision->CollisionNormal = translationVectorPrime.Normalize();
		collision->PenetrationDistance = sphere->GetRadius() - (translationVectorPrime.Magnitude());

		return collision;
	}
	
	Manifold* PhysicsEngine::DetectAABBSphereCollision(ColliderComponent* left, ColliderComponent* right) {
		//Defer to previous definition of this collision
		return DetectSphereAABBCollision(right, left);
	}
}
