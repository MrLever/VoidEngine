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
			auto a = (body->Force / body->Mass);
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
				manifolds.insert(colliders[i]->DetectCollision(colliders[j]));
			}
		}

		return manifolds;
	}

	void PhysicsEngine::ResolveCollisions(std::unordered_set<Manifold*> collisions) {

	}

}
