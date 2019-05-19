//STD Headers

//Library Headers

//Coati Headers
#include "InputInterfaceManager.h"

namespace EngineCore {

	//tors
	InputInterfaceManager::InputInterfaceManager() : Keyboard(0), Mouse(1), Gamepad(2) {

	}


	InputInterfaceManager::~InputInterfaceManager() {

	}

	

	//Private Member Functions

	//Public Member Functions
	void InputInterfaceManager::ReportKeyboardInput(const KeyboardInput &input) {
		Keyboard.PublishInput(input);
	}

	void InputInterfaceManager::ReportMouseKeyInput(const MouseInput &input) {
		Mouse.PublishInput(input);
	}

	void InputInterfaceManager::ReportMousePosition(double x, double y) {
		Mouse.UpdateMousePosition(x, y);
	}

	void InputInterfaceManager::ReportGamepadInput(const GamepadInput &input)	{
		Gamepad.PublishInput(input);
	}

	InputReport<GenericInput<KeyType>> InputInterfaceManager::GetKeyboardEvents() {
		return Keyboard.Poll();
	}

	InputReport <GenericInput<MouseButton>> InputInterfaceManager::GetMouseButtonEvents() {
		return Mouse.Poll();
	}

	InputReport <GenericInput<GamepadButton>> InputInterfaceManager::GetGamepadButtonEvents() {
		return Gamepad.Poll();
	}

}