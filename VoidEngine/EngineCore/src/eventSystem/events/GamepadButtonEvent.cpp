//STD Headers

//Library Headers

//Void Engine Headers
#include "GamepadButtonEvent.h"

namespace core {
	
	GamepadButtonEvent::GamepadButtonEvent(const GamepadInput& input): Input(std::move(input)) {

	}

	utils::Name GamepadButtonEvent::GetEventType() const {
		return utils::Name("GamepadButtonEvent");
	}

	EventCategory GamepadButtonEvent::GetEventCategory() const {
		return EventCategory::RAW_INPUT;
	}

	utils::Name GamepadButtonEvent::GetStaticEventType() {
		return utils::Name("GamepadButtonEvent");
	}

}