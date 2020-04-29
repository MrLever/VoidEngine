//STD Headers

//Library Headers

//Void Engine Headers
#include "event_system/events/AxisInputEvent.h"

namespace core {
	TYPE_INFO_IMPL(AxisInputEvent)

	AxisInputEvent::AxisInputEvent(const AxisInput& input) : Input(input) {
	
	}

	EventCategory AxisInputEvent::GetEventCategory() const {
		return EventCategory::RAW_INPUT;
	}

}