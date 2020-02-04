//STD Headers

//Library Headers

//Void Engine Headers
#include "WindowClosedEvent.h"

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
