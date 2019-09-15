#pragma once
//STD Headers
#include <vector>
#include <memory>
#include <queue>

//Library Headers

//Coati Headers
#include "KeyboardInterface.h"
#include "MouseInterface.h"
#include "GamepadInterface.h"

namespace EngineCore {

	/**
	 * @class InputInterfaceManager
	 * @brief Manages the interfaces for HID devices the engine recognizes
	 */
	class InputInterfaceManager {
	public:
		/**
		 * Constructor
		 */
		InputInterfaceManager();

		/**
		 * Destructor
		 */
		~InputInterfaceManager();

		/**
		 * Callback function for recording captured keyboard input events
		 * @param input The keyboard input being captured
		 */
		void ReportKeyboardInput(const KeyboardInput& input);
		
		/**
		 * Callback function for recording captured mouse button input
		 * @param input The mouse button input being captured
		 */
		void ReportMouseInput(const MouseInput& input);

		/**
		 * Callback function for recording captured mouse scroll wheel events
		 * @param scrollOffset The amount of scroll wheel movement being reported
		 */
		void ReportMouseInput(double scrollOffset);

		/**
		 * Callback function for recording captured mouse movement input
		 * @param x The mouse cursor's new x position
		 * @param y The mouse cursor's new y position
		 */
		void ReportMouseInput(float x, float y);

		/**
		 * Callback function for recording captured gamepad button input
		 * @param input The gamebad input being captured
		 */
		void ReportGamepadInput(const GamepadInput& input);

		/**
		 * Function get get a reference to the current keyboard
		 * @return The engine's active keyboard
		 */
		std::shared_ptr<KeyboardInterface> GetKeyboard();

		/**
		 * Function get get a reference to the current mouse
		 * @return The engine's active mouse
		 */
		std::shared_ptr<MouseInterface> GetMouse();

		/**
		 * Function get get a reference to the current gamepad
		 * @return The engine's active gamepad
		 */
		std::shared_ptr<GamepadInterface> GetGamepad();

	private:
		/** The engine's active keeyboard object */
		std::shared_ptr<KeyboardInterface> Keyboard;

		/** The engine's active mouse object */
		std::shared_ptr<MouseInterface> Mouse;

		/** The engine's active Gamepad object */
		std::shared_ptr<GamepadInterface> Gamepad;
	};

}