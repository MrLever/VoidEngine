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

	class InputInterface {
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
		InputInterface();
		~InputInterface();

	private:

	public:
		//Public Member Functions
		void ReportKeyboardInput(const KeyboardInput &input);
		void ReportMouseKeyInput(const MouseInput &input);
		void ReportMousePosition(double x, double y);
		void ReportGamepadInput(const GamepadInput &input);

		std::vector<KeyboardInput> GetKeyboardEvents();
		std::vector<MouseInput> GetMouseButtonEvents();
		std::vector<GamepadInput> GetGamepadButtonEvents();
	};

}