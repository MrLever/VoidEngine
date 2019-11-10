#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Component.h"

namespace core {
	
	enum class CollisionLayer : unsigned {
		WORLD = 0x01,
		ENTITY = 0x02,
		PLAYER = 0x04,
		ALL = -1
	};

	//Forward class declarations
	class AABBCollider;
	class SphereCollider;

	class Collider {
	public:
		/**
		 * Constructor
		 */
		Collider();

		/**
		 * Constructor
		 */
		Collider(CollisionLayer layer);

		/**
		 * Functions to allow specialized colliders to interact properly
		 * with other colliders
		 */
		virtual bool Collide(AABBCollider* other) = 0;
		virtual bool Collide(SphereCollider* other) = 0;


	private:
		/** Layer(s) this collider interacts with */
		unsigned Layer;
	};

}

