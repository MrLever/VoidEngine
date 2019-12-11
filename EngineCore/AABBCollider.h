#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Collider.h"
#include "ColliderComponent.h"

namespace core {

	class AABBCollider : public Collider {
		/**
		 * Declare custom RTTI support
		 */
		TYPE_INFO_DECL(AABBCollider)

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
		 * Min extent accessor
		 */
		math::Vector3 GetMin() const;

		/**
		 * Min extent accessor
		 */
		math::Vector3 GetMax() const;

	private:
		/** The Min value of the AABB */
		math::Vector3 MinExtent;

		/** The Max Value of the AABB */
		math::Vector3 MaxExtent;
	};

}
