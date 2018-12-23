//STD Headers
#include <memory>

//Library Headers


//Coati Headers
#include "InputManager.h"
#include "MessageBus.h"
#include "Message.h"
#include "WindowManager.h"

//Ctors
InputManager::InputManager(
	std::shared_ptr<MessageBus> GameMessageBus, 
	std::shared_ptr<WindowManager> Window
	) : MessageBusNode(GameMessageBus)
{

	this->GameMessageBus = GameMessageBus;
	Message initMessage("Audio Manager Initialized");
	GameMessageBus.get()->PublishMessage(initMessage);
	this->Window = Window;

}


InputManager::~InputManager() {
}

//Private Member Functions

//Public Member Functions
void InputManager::PollInput() {

}

void InputManager::ReceiveMessage(Message message) {
	std::cout << "Input Manager Message Recieved: \n";
	std::cout << "\t" << message.getEvent() << "\n";
}
