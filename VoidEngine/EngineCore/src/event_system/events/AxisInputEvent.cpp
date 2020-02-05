//STD Headers

//Library Headers

//Void Engine Headers
#include "event_system/events/AxisInputEvent.h"

namespace core {

	AxisInputEvent::AxisInputEvent(const AxisInput& input) : Input(input) {
	
	}

	utils::Name AxisInputEvent::GetEventType() const {
		return utils::Name("AxisInputEvent");
	}

	EventCategory AxisInputEvent::GetEventCategory() const {
		return EventCategory::RAW_INPUT;
	}

	utils::Name AxisInputEvent::GetStaticEventType() {
		return utils::Name("AxisInputEvent");
	}

}