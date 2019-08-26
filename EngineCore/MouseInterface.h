#pragma once
//STD Headers

//Library Headers

//Coati Headers
#include "MouseInput.h"
#include "InputInterface.h"
#include "Vector.h"

namespace EngineCore {

	/**
	 * @class MouseInterface
	 * @brief Provides extra interface functionalities for aquiring mouse position
	 *        and scroll wheel actions
	 */
	class MouseInterface : public InputInterface<MouseInput>{
	public:
		MouseInterface() = default;
		~MouseInterface() = default;

		/**
		 * Callback function for reporting the mouse's position
		 */
		void UpdateMousePosition(double xPos, double yPos);

	private:
		/** The mouse's 2D position in the game's window */
		EngineMath::Vector2<double> Position;
	};

}