//STD Headers
#include <memory>

//Library Headers


//Coati Headers
#include "InputManager.h"
#include "MessageBus.h"
#include "WindowManager.h"

//Ctors
InputManager::InputManager(std::shared_ptr<MessageBus> GameMessageBus, std::shared_ptr<WindowManager> Window) {
	this->GameMessageBus = GameMessageBus;
	this->Window = Window;
}


InputManager::~InputManager() {
}

//Private Member Functions

//Public Member Functions
void InputManager::PollInput() {

}
