//STD Headers

//Library Headers

//Void Engine Headers
#include "GamepadInputEvent.h"

namespace core {
	
	GamepadInputEvent::GamepadInputEvent(const GamepadInput& input): Input(std::move(input)) {

	}

	utils::Name GamepadInputEvent::GetEventType() const {
		return utils::Name("GamepadInputEvent");
	}

	EventCategory GamepadInputEvent::GetEventCategory() const {
		return EventCategory::RAW_INPUT;
	}

	utils::Name GamepadInputEvent::GetStaticEventType() {
		return utils::Name("GamepadInputEvent");
	}

}