//STD Headers

//Library Headers

//Void Engine Headers
#include "MouseMovedEvent.h"

namespace core {
	MouseMovedEvent::MouseMovedEvent(int xPos, int yPos) : Position(xPos, yPos) {
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
