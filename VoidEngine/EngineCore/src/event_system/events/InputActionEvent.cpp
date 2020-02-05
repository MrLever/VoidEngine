//STD Headers

//Library Headers

//Void Engine Headers
#include "event_system/events/InputActionEvent.h"

namespace core {
	InputActionEvent::InputActionEvent(InputAction& action) : Action(action) {

	}

	utils::Name InputActionEvent::GetEventType() const {
		return utils::Name("InputActionEvent");
	}

	EventCategory InputActionEvent::GetEventCategory() const {
		return EventCategory::INPUT;
	}

	utils::Name InputActionEvent::GetStaticEventType() {
		return utils::Name("InputActionEvent");
	}
}
