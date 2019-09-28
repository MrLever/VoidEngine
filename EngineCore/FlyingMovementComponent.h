#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Component.h"

namespace EngineCore {
	
	/**
	 * @class FlyingMovementComponent
	 * @brief The FlyingMovementComponent allows actors (primarily the player actor)
	 *        to respond to player inputs like a flying FPS camera 
	 */
	class FlyingMovementComponent :	public Component {
	public:
		/**
		 * Constructor
		 */
		FlyingMovementComponent(Entity* parent);

		/**
		 * Function to allow the component to update it's parent's position in accordance with 
		 * the player's input
		 * @param input The player's input
		 */
		void Input(const InputEvent& input, float deltaTime) override;

		/**
		 * Setter function for MoveSpeed
		 */
		void SetMoveSpeed(float speed);

		/**
		 * Getter function for MoveSpeed
		 */
		float GetMoveSpeed();


	private:

		/** The movement velocity to be used by this component */
		float MoveSpeed;
	
	};
}
