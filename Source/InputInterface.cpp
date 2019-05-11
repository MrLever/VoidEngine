//STD Headers

//Library Headers

//Coati Headers
#include "InputInterface.h"

namespace EngineCore {

	//tors
	InputInterface::InputInterface() : Keyboard(0), Mouse(1), Gamepad(2) {

	}


	InputInterface::~InputInterface() {

	}

	

	//Private Member Functions

	//Public Member Functions
	void InputInterface::ReportKeyboardInput(KeyboardInput input) {
		Keyboard.ReportInput(input);
	}

	void InputInterface::ReportMouseKeyInput(MouseInput input)	{
		Mouse.ReportInput(input);
	}

	void InputInterface::ReportMousePosition(double x, double y) {
		;
	}

	void InputInterface::ReportGamepadInput(GamepadInput input)	{
		Gamepad.ReportInput(input);
	}

	std::vector<KeyboardInput> InputInterface::GetKeyboardEvents() {
		auto queue = Keyboard.Poll();
		return std::vector<KeyboardInput>(queue.begin(), queue.end());
	}

	std::vector<MouseInput> InputInterface::GetMouseButtonEvents() {
		auto queue = Mouse.Poll();
		return std::vector<MouseInput>(queue.begin(), queue.end());
	}

	std::vector<GamepadInput> InputInterface::GetGamepadButtonEvents() {
		auto queue = Gamepad.Poll();
		return std::vector<GamepadInput>(queue.begin(), queue.end());
	}

}