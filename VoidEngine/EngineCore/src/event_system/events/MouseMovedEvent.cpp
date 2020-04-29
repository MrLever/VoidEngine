//STD Headers

//Library Headers

//Void Engine Headers
#include "event_system/events/MouseMovedEvent.h"

namespace core {
	TYPE_INFO_IMPL(MouseMovedEvent);

	MouseMovedEvent::MouseMovedEvent(double xPos, double yPos) : position((float)xPos, (float)yPos) {
	
	}

	EventCategory MouseMovedEvent::GetEventCategory() const {
		return EventCategory::RAW_INPUT;
	}

}
