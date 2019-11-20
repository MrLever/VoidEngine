#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Collider.h"
#include "ColliderComponent.h"

namespace core {

	class SphereCollider : public Collider {
	public:
		/**
		 * Constructor
		 */
		SphereCollider();

		/**
		 * Set's up sphere collision volume
		 */
		void Initialize() override;
		
		/** Radius Accessor */
		float GetRadius();

		/**
		 * Static callback to generate a manifold for a sphere-sphere collision
		 */
		static Manifold* DetectSphereCollision(ColliderComponent* left, ColliderComponent* right);

		/**
		 * Static callback to resolve a manifold
		 */
		static void ResolveSphereCollision(Manifold* collision);

		/**
		 * Returns dynamic type
		 */
		utils::Name GetTypename() const override;

		/**
		 * Returns name of static Collider Type
		 */
		static utils::Name GetStaticTypename();

	private:
		/** Radius of the collision sphere */
		float Radius;

		/** 
		 * Flag to determine if the callbacks for sphere collisions have 
		 * been registered with the physics engine
		 */
		static bool CallbacksRegistered;
	};

}

