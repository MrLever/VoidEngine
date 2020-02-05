//STD Headers

//Library Headers

//Void Engine Headers
#include "event_system/events/PauseGameEvent.h"

namespace core {

	utils::Name PauseGameEvent::GetEventType() const {
		return utils::Name("PauseGameEvent");
	}

	EventCategory PauseGameEvent::GetEventCategory() const {
		return EventCategory::GAMEPLAY;
	}

	utils::Name PauseGameEvent::GetStaticEventType() {
		return utils::Name("PauseGameEvent");
	}
}
