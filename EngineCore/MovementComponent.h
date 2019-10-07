#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Component.h"

namespace core {

	class MovementComponent : public Component {
	public:
		/**
		 * Constructor
		 */
		MovementComponent(Entity* parent);

		/**
		 * Setter function for MoveSpeed
		 */
		void SetMoveSpeed(float speed);

		/**
		 * Getter function for MoveSpeed
		 */
		float GetMoveSpeed();

	protected:
		/** The movement velocity to be used by this component */
		float MoveSpeed;
	};

}
