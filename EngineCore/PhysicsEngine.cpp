//STD Headers

//Library Headers

//Void Engine Headers
#include "PhysicsEngine.h"
#include "PhysicsComponent.h"
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
			//CorrectPositions(manifold);
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

		//Calculate impulse
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
