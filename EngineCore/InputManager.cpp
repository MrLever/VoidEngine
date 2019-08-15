//STD Headers
#include <memory>
#include <iostream>
#include <utility>

//Library Headers


//Coati Headers
#include "InputManager.h"
#include "MessageBus.h"

namespace EngineCore {

	///CTORS
	InputManager::InputManager(
		std::shared_ptr<InputInterfaceManager> playerInterface,	EngineInterfacePtr engineInterface, const std::string& configFile)
		: Configurable(configFile, engineInterface->GetResourceManager()), 
		  PlayerInterface(std::move(playerInterface)), 
		  VoidEngineInterface(std::move(engineInterface)) {

	}

	///Public Member Functions
	void InputManager::HandleInput() {
		HandleKeyboard();
		HandleMouse();
		HandleGamepad();
	}

	///Private Member Functions

	void InputManager::LoadKeybindings() {
		if (!Bindings.Load()) {
			std::cerr << "Keybindings failed to load\n";
		}
	}

	void InputManager::HandleKeyboard() {
		auto KeyboardEvents = PlayerInterface->GetKeyboardEvents();

		for (const auto& input : KeyboardEvents.Inputs) {
			if (input->GetButtonState() == ButtonState::Pressed)
				std::cout << "Keyboard button Pressed\n";

			if (input->GetButtonState() == ButtonState::Held)
				std::cout << "Keyboard button Held\n";

			if (input->GetButtonState() == ButtonState::Released)
				std::cout << "Keyboard button Released\n";
		}

		//TODO(MrLever): Finsish
	}

	void InputManager::HandleMouse() {
		auto MouseButtonEvents = PlayerInterface->GetMouseButtonEvents();
		
		//TODO(MrLever): Finish
		for (const auto& input : MouseButtonEvents.Inputs) {
			if (input->GetButtonState() == ButtonState::Pressed)
				std::cout << "Mouse button Pressed\n";

			if (input->GetButtonState() == ButtonState::Held)
				std::cout << "Mouse button Held\n";

			if (input->GetButtonState() == ButtonState::Released)
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