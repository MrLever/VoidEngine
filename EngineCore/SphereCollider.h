#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Collider.h"

namespace core {

	class SphereCollider : public Collider {
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

		/** Collision detection functions */
		bool DetectCollision(AABBCollider* other) override;
		bool DetectCollision(SphereCollider* other) override;
	
		/** Radius Accessor */
		float GetRadius();

	private:
		float Radius;
	};

}

