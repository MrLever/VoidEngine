#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Collider.h"

namespace core {

	class AABBCollider : public Collider {
	public:

		/** Collision detection functions */
		bool DetectCollision(AABBCollider* other) override;
		bool DetectCollision(SphereCollider* other) override;

	};

}
