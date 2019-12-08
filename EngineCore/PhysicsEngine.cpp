//STD Headers

//Library Headers

//Void Engine Headers
#include "PhysicsEngine.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "SphereCollider.h"
#include "AABBCollider.h"

namespace core {

	// Static variable initialization
	const float PhysicsEngine::COLLISION_EPSILON = 0.0001f;

	PhysicsEngine::PhysicsEngine(
		EventBus* bus, 
		const utils::ResourceHandle<utils::Configuration>& configuration
	) : EventBusNode(bus), Configurable(configuration) {
		utils::Logger::LogInfo("Initializing Physics Engine Collision System");
		ColliderComponent::RegisterCollisionDetectionCallback<SphereCollider, SphereCollider>(DetectSphereSphereCollision);
		ColliderComponent::RegisterCollisionDetectionCallback<AABBCollider, AABBCollider>(DetectAABBAABBCollision);
	}
	
	void PhysicsEngine::Configure() {
		;
	}

	void PhysicsEngine::ReceiveEvent(Event* event) {
		;
	}
	
	void PhysicsEngine::Simulate(Level* scene, float deltaTime) {
		//Physics simulations update 60 times per second
		static float accumulator = 0.0f;
		static const float PHYSICS_DT = 0.016; 

		accumulator += deltaTime;

		while (accumulator >= PHYSICS_DT) {
			ApplyForces(scene, PHYSICS_DT);
			Integrate(scene, PHYSICS_DT);
			HandleCollisions(scene, PHYSICS_DT);

			accumulator -= PHYSICS_DT;
		}

		//Apply the remainder 
		if (accumulator != 0) {
			ApplyForces(scene, accumulator);
			Integrate(scene, accumulator);
			HandleCollisions(scene, accumulator);
			accumulator = 0;
		}
	}

	void PhysicsEngine::ApplyForces(Level* scene, float deltaTime) {
		auto g = scene->GetAttribute<float>("gravity");
		auto entities = scene->GetScene();
		
		//apply gravity
		for (auto& entity : entities) {
			auto body = entity->GetComponent<PhysicsComponent>();
			if (!body) {
				continue;
			}
			
			auto force = body->GetMass() * g * math::Vector3(0, -1, 0);
			force *= body->GetGravityScale();

			body->ApplyForce(force);
		}
	}

	void PhysicsEngine::Integrate(Level* scene, float deltaTime) {
		auto entities = scene->GetScene();

		//Resolve forces
		for (auto& entity : entities) {
			auto body = entity->GetComponent<PhysicsComponent>();
			if (!body) {
				continue;
			}

			auto x_i = entity->GetPostion();
			auto a = (body->GetForce() * body->GetInverseMass());

			body->AddVelocity(a * deltaTime);

			auto x_f = x_i + (body->GetVelocity() * deltaTime);

			entity->SetPosition(x_f);

			//Clear active forces after resolved
			body->ClearForce();
		}
	}

	void PhysicsEngine::HandleCollisions(Level* scene, float deltaTime) {
		auto manifolds = DetectCollisions(scene);
		ResolveCollisions(manifolds);

		// Destroy manifolds to prevent memory leak
		for (auto& manifold : manifolds) {
			delete manifold;
		}
	}

	std::unordered_set<Manifold*> PhysicsEngine::DetectCollisions(Level* scene) {
		auto Entities = scene->GetScene();

		std::vector<ColliderComponent*> colliders;
		for (auto& entity : Entities) {
			auto collider = entity->GetComponent<ColliderComponent>();
			if (collider) {
				colliders.push_back(collider);
			}
		}

		std::unordered_set<Manifold*> manifolds;
		//O(n^2) Collision detection
		for (int i = 0; i < colliders.size(); i++) {
			for (int j = i+1; j < colliders.size(); j++) {
				auto manifold = colliders[i]->DetectCollision(colliders[j]);
				if (manifold) {
					manifolds.insert(manifold);
				}
			}
		}

		return manifolds;
	}

	void PhysicsEngine::ResolveCollisions(std::unordered_set<Manifold*> collisions) {
		for (auto& manifold : collisions) {
			ResolveCollision(manifold);
			CorrectPositions(manifold);
		}
	}

	void PhysicsEngine::ResolveCollision(Manifold* collision) {
		auto colliderA = collision->ColliderA;
		auto objectA = colliderA->GetParent();
		auto bodyA = objectA->GetComponent<PhysicsComponent>();

		auto colliderB = collision->ColliderB;
		auto objectB = colliderB->GetParent();
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

		auto colliderA = collision->ColliderA;
		auto objectA = colliderA->GetParent();
		auto bodyA = objectA->GetComponent<PhysicsComponent>();

		auto colliderB = collision->ColliderB;
		auto objectB = colliderB->GetParent();
		auto bodyB = objectB->GetComponent<PhysicsComponent>();

		//Gather object masses
		float invMassA = (bodyA == nullptr) ? 0 : bodyA->GetInverseMass();
		float invMassB = (bodyB == nullptr) ? 0 : bodyB->GetInverseMass();

		float correctionConstant = collision->PenetrationDistance / (invMassA + invMassB);
		correctionConstant *= CORRECTION_FACTOR;
		math::Vector3 correctionVector = correctionConstant * collision->CollisionNormal;

		if (bodyA && !bodyA->GetIsStatic()) {
			//Scale positional correction by mass of object
			objectA->SetPosition(objectA->GetPostion() - correctionVector * invMassA);
		}
		if (bodyB && !bodyB->GetIsStatic()) {
			//Scale positional correction by mass of object
			objectB->SetPosition(objectB->GetPostion() + correctionVector * invMassB);
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
		collision->ColliderA = left;
		collision->ColliderB = right;

		//Get direction vector between colliders
		math::Vector3 translationVector = right->GetPosition() - left->GetPosition();

		if (translationVector.Magnitude2() < COLLISION_EPSILON) {
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
		manifold->ColliderA = left;
		manifold->ColliderB = right;

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

}
