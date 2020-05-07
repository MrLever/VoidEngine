#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/event_system/Event.h"
#include "core/input/definitions/AxisInput.h"

namespace core {

	class AxisInputEvent : public Event {
		ENABLE_RTTI(AxisInputEvent)

	public:
		/** The Input being reported */
		AxisInput Input;

		/**
		 * Constructor
		 */
		AxisInputEvent(const AxisInput& input);

	};

}
