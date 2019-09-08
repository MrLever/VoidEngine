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
		: Configurable(configuration), 
		  Keyboard(std::move(playerInterface->GetKeyboard())),
		  Mouse(std::move(playerInterface->GetMouse())),
		  Gamepad(std::move(playerInterface->GetGamepad())),
		  VoidEngineInterface(std::move(engineInterface)) {

	}

	void InputManager::HandleInput() {
		HandleKeyboard();
		HandleMouse();
		HandleGamepad();
	}

	void InputManager::HandleKeyboard() {
		auto KeyboardEvents = Keyboard->Poll();

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
		auto MouseButtonEvents = Mouse->Poll();
		auto cursorPosition = Mouse->PollCursorPosition();
		auto scrollOffset = Mouse->PollScrollOffset();

		if (scrollOffset != 0) {
			std::cout << "Scroll detected, magnitute: " << scrollOffset << "\n";
		}

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
		auto GamepadEvents = Gamepad->Poll();

		//TODO(MrLever): Finish
	}

	void InputManager::Configure() {
		; //TODO (MrLever): Actually configure this thing
	}

}