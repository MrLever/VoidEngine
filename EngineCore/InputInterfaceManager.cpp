//STD Headers

//Library Headers

//Coati Headers
#include "InputInterfaceManager.h"

namespace EngineCore {

	//tors
	InputInterfaceManager::InputInterfaceManager() 
		: Keyboard(std::make_shared<KeyboardInterface>()), 
		  Mouse(std::make_shared<MouseInterface>()), 
		  Gamepad(std::make_shared<GamepadInterface>()) {

	}


	InputInterfaceManager::~InputInterfaceManager() {

	}

	void InputInterfaceManager::ReportKeyboardInput(const KeyboardInput& input) {
		Keyboard->PublishInput(input);
	}

	void InputInterfaceManager::ReportMouseInput(const MouseInput& input) {
		Mouse->PublishInput(input);
	}

	void InputInterfaceManager::ReportMouseInput(double scrollOffset) {
		Mouse->ReportScrollAction(scrollOffset);
	}

	void InputInterfaceManager::ReportMouseInput(double x, double y) {
		Mouse->UpdateMousePosition(x, y);
	}

	void InputInterfaceManager::ReportGamepadInput(const GamepadInput& input) {
		Gamepad->PublishInput(input);
	}

	std::shared_ptr<KeyboardInterface> InputInterfaceManager::GetKeyboard(){
		return Keyboard;
	}

	std::shared_ptr<MouseInterface> InputInterfaceManager::GetMouse() {
		return Mouse;
	}

	std::shared_ptr<GamepadInterface> InputInterfaceManager::GetGamepad()
	{
		return Gamepad;
	}

}