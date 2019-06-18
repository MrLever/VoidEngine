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

	class InputInterfaceManager {
		//Forward class Definitions

	public:
		//Public Class members

	private:
		//Private Class Members
		KeyboardInterface Keyboard;
		MouseInterface Mouse;
		GamepadInterface Gamepad;

	public:
		//tors
		InputInterfaceManager();
		~InputInterfaceManager();

	private:

	public:
		//Public Member Functions
		void ReportKeyboardInput(const KeyboardInputPtr input);
		void ReportMouseKeyInput(const MouseInputPtr input);
		void ReportMousePosition(double x, double y);
		void ReportGamepadInput(const GamepadInputPtr input);

		InputReport GetKeyboardEvents();
		InputReport GetMouseButtonEvents();
		InputReport GetGamepadButtonEvents();
	};

}