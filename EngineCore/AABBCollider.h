#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "ColliderComponent.h"

namespace core {

	class AABBCollider : public ColliderComponent {
	public:
		/**
		 * Sets up collision volume data
		 */
		void Initialize() override;
		
		math::Vector3 Min;
		math::Vector3 Max;


	};

}
