//STD Headers

//Library Headers

//Coati Headers
#include "InputInterfaceManager.h"

namespace EngineCore {

	//tors
	InputInterfaceManager::InputInterfaceManager() : Keyboard(), Mouse(), Gamepad() {

	}


	InputInterfaceManager::~InputInterfaceManager() {

	}

	

	//Private Member Functions

	//Public Member Functions
	void InputInterfaceManager::ReportKeyboardInput(const KeyboardInput& input) {
		Keyboard.PublishInput(input);
	}

	void InputInterfaceManager::ReportMouseKeyInput(const MouseInput& input) {
		Mouse.PublishInput(input);
	}

	void InputInterfaceManager::ReportMousePosition(double x, double y) {
		Mouse.UpdateMousePosition(x, y);
	}

	void InputInterfaceManager::ReportGamepadInput(const GamepadInput& input)	{
		Gamepad.PublishInput(input);
	}

	InputReport<KeyboardInput> InputInterfaceManager::GetKeyboardEvents() {
		return Keyboard.Poll();
	}

	InputReport<MouseInput> InputInterfaceManager::GetMouseButtonEvents() {
		return Mouse.Poll();
	}

	InputReport<GamepadInput> InputInterfaceManager::GetGamepadButtonEvents() {
		return Gamepad.Poll();
	}

}