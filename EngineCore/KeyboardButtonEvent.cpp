//STD Headers

//Library Headers

//Void Engine Headers
#include "KeyboardButtonEvent.h"

namespace core {
	KeyboardButtonEvent::KeyboardButtonEvent(KeyboardInput& input) : Input(input) {

	}

	utils::Name KeyboardButtonEvent::GetEventType() const{
		return  utils::Name("KeyboardButtonEvent");
	}

	EventCategory KeyboardButtonEvent::GetEventCategory() const {
		return EventCategory::RAW_INPUT;
	}

	utils::Name KeyboardButtonEvent::GetStaticEventType() {
		return utils::Name("KeyboardButtonEvent");
	}
}
