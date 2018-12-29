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

	PublishMessage("Input Manager Initialized", Initialization);
}


InputManager::~InputManager() {
}


//Private Member Functions

void InputManager::LoadKeybindings() {
	Bindings.Load();
}

//Public Member Functions

void InputManager::HandleInput(KeyboardInput input) {
	PublishMessage(Bindings.GetBinding(input));
}

void InputManager::RegisterReciever() {
	GameMessageBus->AddReciever(this, Input);
}

void InputManager::ReceiveMessage(Message message) {
	std::cout << "Input Manager Message Recieved: \n";
	std::cout << "\t" << message.getEvent() << "\n";
}
