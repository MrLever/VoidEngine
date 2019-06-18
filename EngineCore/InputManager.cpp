//STD Headers
#include <memory>
#include <iostream>
#include <utility>

//Library Headers


//Coati Headers
#include "InputManager.h"
#include "MessageBus.h"

namespace EngineCore {

	//Ctors
	InputManager::InputManager(
		std::shared_ptr<MessageBus> bus,
		std::shared_ptr<InputInterfaceManager> playerInterface
	) : MessageBusNode(std::move(bus)), PlayerInterface(std::move(playerInterface)) {

		this->RegisterReciever();
		this->RegisterEvents();

		PublishMessage("Input Manager Initialized", MessageType::Initialization);
	}


	//Private Member Functions

	void InputManager::LoadKeybindings() {
		if (!Bindings.Load()) {
			PublishMessage("Keybinding failed to load", MessageType::Termination);
		}
	}

	//Protected Member Functions

	void InputManager::RegisterReciever() {
		GameMessageBus->AddReceiver(
			this,
			MessageType::Initialization
		);
	}

	void InputManager::RegisterEvents() {
		//Input manager does not react to incomming messages.
	}


	//Private Member Functions
	
	void InputManager::HandleKeyboard() {
		auto KeyboardEvents = PlayerInterface->GetKeyboardEvents();

		for (const auto& input : KeyboardEvents.Inputs) {
			if (input->GetButtonState() == ButtonState::Pressed)
				PublishMessage(Message("Keyboard button Pressed", MessageType::Input));

			if (input->GetButtonState() == ButtonState::Held)
				PublishMessage(Message("Keyboard button held", MessageType::Input));

			if (input->GetButtonState() == ButtonState::Released)
				PublishMessage(Message("Keyboard button released", MessageType::Input));
		}

		//TODO(MrLever): Finsish
	}

	void InputManager::HandleMouse() {
		auto MouseButtonEvents = PlayerInterface->GetMouseButtonEvents();
		
		//TODO(MrLever): Finish
		for (const auto& input : MouseButtonEvents.Inputs) {
			if(input->GetButtonState() == ButtonState::Pressed)
				PublishMessage(Message("Mouse button Pressed", MessageType::Input));

			if(input->GetButtonState() == ButtonState::Held)
				PublishMessage(Message("Mouse button held", MessageType::Input));

			if(input->GetButtonState() == ButtonState::Released)
				PublishMessage(Message("Mouse button released", MessageType::Input));
		}
	}

	void InputManager::HandleGamepad() {
		auto GamepadEvents = PlayerInterface->GetGamepadButtonEvents();

		//TODO(MrLever): Finish
	}

	//Public Member Functions

	void InputManager::HandleInput() {
		HandleKeyboard();
		HandleMouse();
		HandleGamepad();
	}

	void InputManager::ReceiveMessage(const Message &message) {
		//Input manager does not react to incomming messages.
	}

}