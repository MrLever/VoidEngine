#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Component.h"
#include "Collider.h"

namespace core {

	class ColliderComponent : public Component {
	public:
		/**
		 * Constructor
		 */
		ColliderComponent();

		/**
		 * Sets up CollisionVolume
		 */
		void Initialize() override;

	private:
		Collider* CollisionVolume;
	};

}

