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
		/** The Min value of the AABB */
		math::Vector3 MinExtent;

		/** The Max Value of the AABB */
		math::Vector3 MaxExtent;
	};

}
