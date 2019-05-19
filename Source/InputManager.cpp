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

		//TODO(MrLever): Finsish
	}

	void InputManager::HandleMouse() {
		auto MouseButtonEvents = PlayerInterface->GetMouseButtonEvents();
		//TODO(MrLever): Finish
	}


	//Public Member Functions

	void InputManager::AddKeyBinding(const KeyboardInput &input, const Message &message) {
		Bindings.AddBinding(input, message);
	}



	void InputManager::HandleInput() {
		HandleKeyboard();
		//HandleMouse();
	}

	void InputManager::ReceiveMessage(const Message &message) {
		//Input manager does not react to incomming messages.
	}

}