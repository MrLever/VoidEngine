//STD Headers
#include <memory>
#include <iostream>

//Library Headers


//Coati Headers
#include "InputManager.h"
#include "MessageBus.h"
#include "Message.h"
#include "WindowManager.h"

//Ctors
InputManager::InputManager(
	std::shared_ptr<MessageBus> Bus, 
	std::shared_ptr<WindowManager> Window
	) :  MessageBusNode(GameMessageBus)
{
	this->GameMessageBus = Bus;
	this->RegisterReciever();
	this->Window = Window;


	Message outgoing("Input Manager Initialized", Initialization);
	GameMessageBus.get()->PublishMessage(outgoing);

}


InputManager::~InputManager() {
}

//Private Member Functions

//Public Member Functions
void InputManager::PollInput() {

}

void InputManager::RegisterReciever() {
	GameMessageBus->AddReciever(this, Initialization);
}

void InputManager::ReceiveMessage(Message message) {
	std::cout << "Input Manager Message Recieved: \n";
	std::cout << "\t" << message.getEvent() << "\n";
}
