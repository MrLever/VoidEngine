//STD Headers
#include <memory>
#include <iostream>

//Library Headers


//Coati Headers
#include "InputManager.h"
#include "MessageBus.h"

namespace EngineCore {

	//Ctors
	InputManager::InputManager(
		std::shared_ptr<MessageBus> Bus,
		std::shared_ptr<InputInterface> userInterface
	) : MessageBusNode(Bus), PlayerInterface(userInterface) {

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


	//Private Member Functions
	
	void InputManager::HandleKeyboard() {
		auto KeyboardEvents = PlayerInterface->GetKeyboardEvents();

		//TODO: Finsish
	}

	void InputManager::HandleMouse() {
		auto MouseButtonEvents = PlayerInterface->GetMouseButtonEvents();
		//TODO: Finish
	}


	//Public Member Functions

	void InputManager::AddKeyBinding(KeyboardInput input, Message message) {
		Bindings.AddBinding(input, message);
	}



	void InputManager::HandleInput() {
		HandleKeyboard();
		//HandleMouse();
	}

	void InputManager::ReceiveMessage(Message message) {
		//Input manager does not react to incomming messages.
	}

}