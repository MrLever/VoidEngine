//STD Headers

//Library Headers

//Void Engine Headers
#include "PhysicsEngine.h"
#include "ColliderComponent.h"

namespace core {
	PhysicsEngine::PhysicsEngine(
		EventBus* bus, 
		const utils::ResourceHandle<utils::Configuration>& configuration
	) : EventBusNode(bus), Configurable(configuration) {

	}
	
	void PhysicsEngine::Configure() {
		;
	}

	void PhysicsEngine::ReceiveEvent(Event* event) {
		;
	}
	
	void PhysicsEngine::Simulate(Level* scene, float deltaTime) {
		ApplyForces(scene, deltaTime);
		Integrate(scene, deltaTime);
		HandleCollisions(scene, deltaTime);
	}


	void PhysicsEngine::ApplyForces(Level* scene, float deltaTime) {
		auto g = scene->GetAttribute<float>("gravity");
		auto entities = scene->GetScene();
		
		//apply gravity
		for (auto& entity : entities) {
			auto body = entity->GetBody();
			if (!body->PhysicsEnabled) {
				continue;
			}

			auto force = body->Mass * g * math::Vector3(0, -1, 0);
			body->Force = force;
		}
	}

	void PhysicsEngine::Integrate(Level* scene, float deltaTime) {
		auto entities = scene->GetScene();

		//Resolve forces
		for (auto& entity : entities) {
			auto body = entity->GetBody();
			if (!body->PhysicsEnabled) {
				continue;
			}

			auto x_i = entity->GetPostion();
			auto a = (body->Force * body->InverseMass);
			a *= deltaTime;

			body->Velocity += a;

			auto x_f = x_i + (body->Velocity * deltaTime);

			entity->SetPosition(x_f);

			//Clear active forces after resolved
			body->Force = math::Vector3();
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

	void PhysicsEngine::CorrectPositions(Manifold* collision) {
		const float MAX_PEN = 0.01f;
		const float CORRECTION_FACTOR = 0.4f;

		auto colliderA = collision->ColliderA;
		auto objectA = colliderA->GetParent();
		auto bodyA = objectA->GetBody();

		auto colliderB = collision->ColliderB;
		auto objectB = colliderB->GetParent();
		auto bodyB = objectB->GetBody();


		float correctionConstant = std::max(collision->PenetrationDistance - MAX_PEN, 0.0f);
		if (correctionConstant == 0) {
			//If the objects penetration distance is under the maximum tolerance, short circuit
			return;
		}

		correctionConstant /= (bodyA->InverseMass + bodyB->InverseMass);
		correctionConstant *= CORRECTION_FACTOR;
		math::Vector3 correctionVector = correctionConstant * collision->CollisionNormal;

		if (bodyA->PhysicsEnabled) {
			objectA->SetPosition(objectA->GetPostion() - correctionVector);
		}
		if (bodyB->PhysicsEnabled) {
			objectB->SetPosition(objectB->GetPostion() + correctionVector);
		}
	}

}
