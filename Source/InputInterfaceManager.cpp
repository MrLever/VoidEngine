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
	void InputInterfaceManager::ReportKeyboardInput(const KeyboardInputPtr input) {
		Keyboard.PublishInput(input);
	}

	void InputInterfaceManager::ReportMouseKeyInput(const MouseInputPtr input) {
		Mouse.PublishInput(input);
	}

	void InputInterfaceManager::ReportMousePosition(double x, double y) {
		Mouse.UpdateMousePosition(x, y);
	}

	void InputInterfaceManager::ReportGamepadInput(const GamepadInputPtr input)	{
		Gamepad.PublishInput(input);
	}

	InputReport InputInterfaceManager::GetKeyboardEvents() {
		return Keyboard.Poll();
	}

	InputReport InputInterfaceManager::GetMouseButtonEvents() {
		return Mouse.Poll();
	}

	InputReport InputInterfaceManager::GetGamepadButtonEvents() {
		return Gamepad.Poll();
	}

}