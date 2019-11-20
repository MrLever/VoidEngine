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
	void PhysicsEngine::Simulate(Level* scene) {
		auto manifolds = DetectCollisions(scene);
		ResolveCollisions(manifolds);
		
		// Destroy manifolds to prevent memory leak
		for (auto& manifold : manifolds) {
			delete manifold;
		}
	}

	void PhysicsEngine::Configure() {
		;
	}

	void PhysicsEngine::ReceiveEvent(Event* event) {
		;
	}

	std::unordered_set<Manifold*> PhysicsEngine::DetectCollisions(Level* scene) {
		auto Entities = scene->GetScene();

		std::vector<ColliderComponent*> colliders;
		for (auto& entity : Entities) {
			colliders.push_back(entity->GetComponent<ColliderComponent>());
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
