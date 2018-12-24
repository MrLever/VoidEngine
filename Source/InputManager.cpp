//STD Headers
#include <memory>
#include <iostream>

//Library Headers


//Coati Headers
#include "InputManager.h"
#include "MessageBus.h"
#include "WindowManager.h"

//Ctors
InputManager::InputManager(
	std::shared_ptr<MessageBus> Bus, 
	std::shared_ptr<WindowManager> Window
	) : MessageBusNode(Bus)
{
	this->RegisterReciever();
	this->Window = Window;


	PublishMessage("Input Manager Initialized", Initialization);
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
