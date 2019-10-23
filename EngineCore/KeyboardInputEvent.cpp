//STD Headers

//Library Headers

//Void Engine Headers
#include "KeyboardInputEvent.h"

namespace core {
	KeyboardInputEvent::KeyboardInputEvent(KeyboardInput& input) : Input(input) {

	}

	utils::Name KeyboardInputEvent::GetEventType() const{
		return  utils::Name("KeyboardInputEvent");
	}

	EventCategory KeyboardInputEvent::GetEventCategory() const {
		return EventCategory::RAW_INPUT;
	}

	utils::Name KeyboardInputEvent::GetStaticEventType() {
		return utils::Name("KeyboardInputEvent");
	}
}
