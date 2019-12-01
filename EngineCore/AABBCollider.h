#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Collider.h"
#include "ColliderComponent.h"

namespace core {

	class AABBCollider : public Collider {
	public:
		/**
		 * Constructor
		 */
		AABBCollider();

		/**
		 * Applies configuration settings
		 */
		void Initialize() override;

		/**
		 * Static callback to generate a manifold for a sphere-sphere collision
		 */
		static Manifold* DetectAABBCollision(ColliderComponent* left, ColliderComponent* right);

		/**
		 * Min extent accessor
		 */
		math::Vector3 GetMin() const;

		/**
		 * Min extent accessor
		 */
		math::Vector3 GetMax() const;

		/**
		 * Returns dynamic type
		 */
		utils::Name GetTypename() const override;

		/**
		 * Returns name of static Collider Type
		 */
		static utils::Name GetStaticTypename();
	
	private:
		math::Vector3 MinExtent;
		math::Vector3 MaxExtent;

		/**
		 * Flag to determine if the callbacks for sphere collisions have
		 * been registered with the physics engine
		 */
		static bool CallbacksRegistered;
	};

}
