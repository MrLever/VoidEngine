#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "ColliderComponent.h"

namespace core {

	class SphereCollider : public ColliderComponent {
	public:
		/**
		 * Constructor
		 * Contructs a unit sphere collider
		 */
		SphereCollider();
		
		/**
		 * Constructor
		 * Contructs a sphere collider with radius r
		 */
		SphereCollider(float r);

		/**
		 * Sets up CollisionVolume
		 */
		void Initialize() override;
	
		/** Radius Accessor */
		float GetRadius();

	private:
		float Radius;
	};

}

