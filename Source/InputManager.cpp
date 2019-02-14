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
		{ MessageType::Initialization, MessageType::Initialization }
	);
}

void InputManager::RegisterEvents() {
	//TODO Add to Events Map
}



//Public Member Functions

void InputManager::HandleInput(KeyboardInput input) {
	PublishMessage(Bindings.GetBinding(input));
}

void InputManager::ReceiveMessage(Message message) {
	//Lookup incomming message in event map and execute related function
	if (Events[message]) {
		Events[message]();
	}
}
