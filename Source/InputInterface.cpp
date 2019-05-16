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
	void InputInterface::ReportKeyboardInput(const KeyboardInput &input) {
		Keyboard.PublishInput(input);
	}

	void InputInterface::ReportMouseKeyInput(const MouseInput &input) {
		Mouse.PublishInput(input);
	}

	void InputInterface::ReportMousePosition(double x, double y) {
		Mouse.UpdateMousePosition(x, y);
	}

	void InputInterface::ReportGamepadInput(const GamepadInput &input)	{
		Gamepad.PublishInput(input);
	}

	InputReport<GenericInput<KeyType>> InputInterface::GetKeyboardEvents() {
		return Keyboard.Poll();
	}

	InputReport <GenericInput<MouseButton>> InputInterface::GetMouseButtonEvents() {
		return Mouse.Poll();
	}

	InputReport <GenericInput<GamepadButton>> InputInterface::GetGamepadButtonEvents() {
		return Gamepad.Poll();
	}

}