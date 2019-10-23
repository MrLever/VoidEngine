//STD Headers

//Library Headers

//Void Engine Headers
#include "WindowCloseEvent.h"

namespace core {
	utils::Name WindowCloseEvent::GetEventType() const {
		return utils::Name("WindowCloseEvent");
	}

	EventCategory WindowCloseEvent::GetEventCategory() const {
		return EventCategory::WINDOW;
	}

	utils::Name WindowCloseEvent::GetStaticEventType() {
		return utils::Name("WindowCloseEvent");
	}
}
