//STD Headers

//Library Headers

//Void Engine Headers
#include "input/InputAction.h"

namespace core {
	InputAction::InputAction(const std::string& action) : Action(std::move(action)), Type(ActionType::PRESSED) {

	}

	InputAction::InputAction(const utils::Name& action) : Action(std::move(action)), Type(ActionType::PRESSED) {

	}

	InputAction::InputAction(const std::string& action, ActionType type) : Action(std::move(action)), Type(type) {

	}

	InputAction::InputAction(const utils::Name& action, ActionType type) : Action(std::move(action)), Type(type) {

	}

	bool InputAction::operator==(const InputAction& other) const {
		return Action == other.Action && Type == other.Type;
	}
}
