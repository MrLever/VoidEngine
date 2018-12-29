//STD Headers
#include <memory>
#include <iostream>

//Library Headers


//Coati Headers
#include "InputManager.h"
#include "MessageBus.h"


//Ctors
InputManager::InputManager( std::shared_ptr<MessageBus> Bus) : MessageBusNode(Bus){
	this->RegisterReciever();

	PublishMessage("Input Manager Initialized", MessageType::Initialization);
}


InputManager::~InputManager() {
}


//Private Member Functions

void InputManager::LoadKeybindings() {
	if (!Bindings.Load()) {
		PublishMessage("Keybinding failed to load", MessageType::Termination);
	}
}

//Public Member Functions

void InputManager::HandleInput(KeyboardInput input) {
	if (input.GetKeyState() == KeyState::Released || input.GetKeyState() == KeyState::Held) {
		return;
	}
	PublishMessage(Bindings.GetBinding(input));
}

void InputManager::RegisterReciever() {
	GameMessageBus->AddReceiver(this, { MessageType::Initialization, MessageType::Initialization });
}

void InputManager::ReceiveMessage(Message message) {
	std::cout << "Input Manager Message Recieved: \n";
	std::cout << "\t" << message.getEvent() << "\n";
}
