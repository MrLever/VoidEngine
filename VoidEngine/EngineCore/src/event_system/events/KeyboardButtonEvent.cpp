//STD Headers

//Library Headers

//Void Engine Headers
#include "event_system/events/KeyboardButtonEvent.h"

namespace core {
	TYPE_INFO_IMPL(KeyboardButtonEvent)

	KeyboardButtonEvent::KeyboardButtonEvent(KeyboardInput& input) : input(input) {

	}

	EventCategory KeyboardButtonEvent::GetEventCategory() const {
		return EventCategory::RAW_INPUT;
	}

}
