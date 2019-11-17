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
		 */
		SphereCollider();

		/**
		 * Set's up sphere collision volume
		 */
		void Initialize() override;
		
		/** Radius Accessor */
		float GetRadius();

	private:
		/** Radius of the collision sphere */
		float Radius;
	};

}

