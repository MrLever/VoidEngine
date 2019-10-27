//STD Headers

//Library Headers

//Void Engine Headers
#include "InputAction.h"

namespace core {
	InputAction::InputAction(const std::string& action) : Action(std::move(action)), Data(0) {

	}
}
