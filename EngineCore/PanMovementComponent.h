#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "MovementComponent.h"

namespace core {
	/**
	 * @class PanMovementComponent
	 * @brief Class that allows entities to be controlled 
	 *        with movement restricted to a plane
	 */
	class PanMovementComponent : public MovementComponent {
	public:
		/**
		 * Constructor
		 * @param parent The Entity this Component is attatched to
		 */
		PanMovementComponent(Entity* parent);

		/**
		 * Function to allow the component to update it's parent's position in accordance with
		 * the player's input
		 * @param input The player's input
		 */
		void Input(const InputEvent& input, float deltaTime) override;

		/**
		 * Function to allow the component to update it's parent's position in accordance with
		 * the player's input
		 * @param input The player's input
		 */
		void Input(const InputAxis& axis, float deltaTime) override;
	};

}
