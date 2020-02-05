//STD Headers

//Library Headers

//Void Engine Headers
#include "event_system/events/MouseMovedEvent.h"

namespace core {
	MouseMovedEvent::MouseMovedEvent(double xPos, double yPos) : Position((float)xPos, (float)yPos) {
	
	}

	utils::Name MouseMovedEvent::GetEventType() const {
		return  utils::Name("MouseMovedEvent");
	}

	EventCategory MouseMovedEvent::GetEventCategory() const {
		return EventCategory::RAW_INPUT;
	}

	utils::Name MouseMovedEvent::GetStaticEventType() {
		return utils::Name("MouseMovedEvent");
	}
}
