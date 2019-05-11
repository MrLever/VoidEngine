//STD Headers

//Library Headers

//Coati Headers
#include "InputInterface.h"

namespace EngineCore {

	//tors
	InputInterface::InputInterface() : Keyboard(0), Mouse(1), Gamepad(2) {

	}


	InputInterface::~InputInterface() {

	}

	//Private Member Functions

	//Public Member Functions
	std::shared_ptr<KeyboardInterface> InputInterface::GetKeyboardInterface() {
		return std::make_shared<KeyboardInterface>(Keyboard);
	}

	std::shared_ptr<MouseInterface> InputInterface::GetMouseInterface() {
		return std::make_shared<MouseInterface>(Mouse);
	}

}