#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Collider.h"

namespace core {

	class AABBCollider : public Collider {
	public:
		/** Collision detection functions */
		bool Collide(AABBCollider* other) override;
		bool Collide(SphereCollider* other) override;

	};

}
