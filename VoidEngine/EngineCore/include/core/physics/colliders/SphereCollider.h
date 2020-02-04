#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Collider.h"
#include "ColliderComponent.h"

namespace core {

	class SphereCollider : public Collider {
		/**
		 * Declare custom RTTI support
		 */
		TYPE_INFO_DECL(SphereCollider)

	public:
		/**
		 * Constructor
		 */
		SphereCollider();

		/**
		 * Set's up sphere collision volume
		 */
		void Initialize() override;
		
		/** 
		 * Radius Accessor 
		 */
		float GetRadius() const;

	private:
		/** Radius of the collision sphere */
		float Radius;

	};

}

