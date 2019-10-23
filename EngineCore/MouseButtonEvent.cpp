//STD Headers

//Library Headers

//Void Engine Headers
#include "MouseButtonEvent.h"

namespace core {
	MouseButtonEvent::MouseButtonEvent(MouseInput& input) : Input(input) {

	}

	utils::Name MouseButtonEvent::GetEventType() const {
		return  utils::Name("MouseButtonEvent");
	}

	EventCategory MouseButtonEvent::GetEventCategory() const {
		return EventCategory::RAW_INPUT;
	}

	utils::Name MouseButtonEvent::GetStaticEventType() {
		return utils::Name("MouseButtonEvent");
	}
}
