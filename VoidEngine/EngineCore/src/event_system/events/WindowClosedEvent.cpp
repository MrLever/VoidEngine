//STD Headers

//Library Headers

//Void Engine Headers
#include "event_system/events/WindowClosedEvent.h"

namespace core {
	utils::Name WindowClosedEvent::GetEventType() const {
		return utils::Name("WindowClosedEvent");
	}

	EventCategory WindowClosedEvent::GetEventCategory() const {
		return EventCategory::WINDOW;
	}

	utils::Name WindowClosedEvent::GetStaticEventType() {
		return utils::Name("WindowClosedEvent");
	}
}
