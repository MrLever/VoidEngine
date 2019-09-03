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
		/**
		 * Callback function for reporting the mouse's position
		 * @param xPos the mouse cursor's X-Coordinate
		 * @param yPos the mouse cursor's Y-Coordinate
		 */
		void UpdateMousePosition(double xPos, double yPos);

		/**
		 * Callback function to allow scroll actions to be reported to the input manager
		 * @param delta The reported scroll movement (Positive means up)
		 */
		void ReportScrollAction(double delta);

		/**
		 * Function to allow user to poll most recent cursor position
		 * @return The cursor's current position
		 */
		EngineMath::Vector2<double> PollCursorPosition();

		/**
		 * Function to allow user to poll most recent scroll action
		 * @return The scroll wheel's delta since the last poll (0 means no action)
		 */
		double PollScrollOffset();

	private:
		/** The total delta of the scroll wheel since the last polling */
		double ScrollOffset;

		/** The mouse's 2D position in the game's window */
		EngineMath::Vector2<double> CursorPosition;
	};

}