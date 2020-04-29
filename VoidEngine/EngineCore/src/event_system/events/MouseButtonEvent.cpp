//STD Headers

//Library Headers

//Void Engine Headers
#include "event_system/events/MouseButtonEvent.h"

namespace core {
	TYPE_INFO_IMPL(MouseButtonEvent);

	MouseButtonEvent::MouseButtonEvent(MouseInput& input) : Input(input) {

	}

	EventCategory MouseButtonEvent::GetEventCategory() const {
		return EventCategory::RAW_INPUT;
	}

}
