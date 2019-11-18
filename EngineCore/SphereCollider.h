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

		static bool DetectSphereCollision(ColliderComponent* left, ColliderComponent* right);

		/**
		 * Returns dynamic type
		 */
		utils::Name GetTypename() override;

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

