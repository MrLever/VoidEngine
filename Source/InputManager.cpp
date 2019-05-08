//STD Headers
#include <memory>
#include <iostream>

//Library Headers


//Coati Headers
#include "InputManager.h"
#include "MessageBus.h"

namespace EngineCore {

	//Ctors
	InputManager::InputManager(std::shared_ptr<MessageBus> Bus) : MessageBusNode(Bus) {
		this->RegisterReciever();
		this->RegisterEvents();

		PublishMessage("Input Manager Initialized", MessageType::Initialization);
	}


	InputManager::~InputManager() {
		PublishMessage("Input Manager Destroyed", MessageType::Termination);
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



	//Public Member Functions

	void InputManager::HandleInput(KeyboardInput input) {
		PublishMessage(Bindings.GetBinding(input));
	}

	void InputManager::ReceiveMessage(Message message) {
		//Input manager does not react to incomming messages.
	}

}