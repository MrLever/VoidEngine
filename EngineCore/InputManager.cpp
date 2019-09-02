//STD Headers
#include <memory>
#include <iostream>
#include <utility>

//Library Headers


//Coati Headers
#include "InputManager.h"
#include "MessageBus.h"

namespace EngineCore {

	InputManager::InputManager(
		std::shared_ptr<InputInterfaceManager> playerInterface,	EngineInterfacePtr engineInterface, const EngineUtils::ResourceHandle& configuration)
		: Configurable(configuration), PlayerInterface(std::move(playerInterface)), 
		  VoidEngineInterface(std::move(engineInterface)) {

	}

	void InputManager::HandleInput() {
		HandleKeyboard();
		HandleMouse();
		HandleGamepad();
	}

	void InputManager::HandleKeyboard() {
		auto KeyboardEvents = PlayerInterface->GetKeyboardEvents();

		for (const auto& input : KeyboardEvents.Inputs) {
			if (input.GetButtonState() == ButtonState::PRESSED)
				std::cout << "Keyboard button Pressed\n";

			if (input.GetButtonState() == ButtonState::HELD)
				std::cout << "Keyboard button Held\n";

			if (input.GetButtonState() == ButtonState::RELEASED)
				std::cout << "Keyboard button Released\n";
		}

		//TODO(MrLever): Finsish
	}

	void InputManager::HandleMouse() {
		auto MouseButtonEvents = PlayerInterface->GetMouseButtonEvents();
		
		//TODO(MrLever): Finish
		for (const auto& input : MouseButtonEvents.Inputs) {
			if (input.GetButtonState() == ButtonState::PRESSED)
				std::cout << "Mouse button Pressed\n";

			if (input.GetButtonState() == ButtonState::HELD)
				std::cout << "Mouse button Held\n";

			if (input.GetButtonState() == ButtonState::RELEASED)
				std::cout << "Mouse button Released\n";
		}
	}

	void InputManager::HandleGamepad() {
		auto GamepadEvents = PlayerInterface->GetGamepadButtonEvents();

		//TODO(MrLever): Finish
	}

	void InputManager::Configure() {
		; //TODO (MrLever): Actually configure this thing
	}

}