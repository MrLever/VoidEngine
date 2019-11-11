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

		/**
		 * Returns name of dynamic Component Type
		 */
		utils::Name GetTypename() override;

		/**
		 * Returns name of static Component Type
		 */
		static utils::Name GetStaticTypename();

	private:
		Collider* CollisionVolume;
	};

}

