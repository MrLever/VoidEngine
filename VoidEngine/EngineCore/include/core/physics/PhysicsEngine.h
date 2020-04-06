#pragma once
//STD Headers
#include <unordered_set>

//Library Headers

//Void Engine Headers
#include "utils/configuration/Configurable.h"

#include "core/Level.h"
#include "core/event_system/EventBusNode.h"
#include "core/physics/Manifold.h"
#include "core/physics/components/PhysicsComponent.h"
#include "core/physics/components/ColliderComponent.h"

namespace core {

	//Forward class declarations
	class ColliderComponent;

	class PhysicsEngine : public EventBusNode, public utils::Configurable {
	public:
		/**
		 * Constructor
		 */
		PhysicsEngine(
			EventBus* bus,
			const utils::ResourceHandle<utils::Configuration>& configuration
		);

		/**
		 * Allows the engine to perform physics updates on the scene
		 */
		void Simulate(const std::vector<std::unique_ptr<Entity>>& entities, float deltaTime);

		/**
		 * Applies physics engine settings
		 */
		void Configure() override;

		/**
		 * Allows PhysicsEngine to recieve incomming events
		 */
		void ReceiveEvent(Event* event) override;

		/**
		 * Set's the gravity strength used for the simulation
		 */
		void SetGravity(float gravity);

	private:
		/**
		 * Applies any special forces to entities in scene
		 */
		void ApplyForces(std::vector<PhysicsComponent*>& physicsComponents, float deltaTime);

		/**
		 * Applies laws of physics to update positions of entities in scene
		 */
		void Integrate(std::vector<PhysicsComponent*>& physicsComponents, float deltaTime);

		/**
		 * Detects and resolves collisions in scene
		 */
		void HandleCollisions(std::vector<ColliderComponent*>& colliders, float deltaTime);

		/**
		 * Generates a set of valid collisions that must be resolved
		 */
		std::unordered_set<Manifold*> DetectCollisions(std::vector<ColliderComponent*>& colliders);

		/**
		 * Resolves collisions and applies impulses
		 */
		void ResolveCollisions(std::unordered_set<Manifold*>& collisions);

		/**
		 * Resolve a single collision manifold
		 */
		void ResolveCollision(Manifold* collision);

		/**
		 * Apply positional correction to prevent sinking object problem
		 */
		void CorrectPositions(Manifold* collision);

		float Gravity;

		static Manifold* DetectSphereSphereCollision(ColliderComponent* left, ColliderComponent* right);

		static Manifold* DetectAABBAABBCollision(ColliderComponent* left, ColliderComponent* right);

		static Manifold* DetectSphereAABBCollision(ColliderComponent* left, ColliderComponent* right);

		static Manifold* DetectAABBSphereCollision(ColliderComponent* left, ColliderComponent* right);

		static const float COLLISION_EPSILON;
	};

}

