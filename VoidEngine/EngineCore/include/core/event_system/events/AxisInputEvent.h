#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/event_system/events/Event.h"
#include "input/definitions/AxisInput.h"

namespace core {

	class AxisInputEvent : public Event {
		TYPE_INFO_DECL(AxisInputEvent)

	public:
		/**
		 * Constructor
		 */
		AxisInputEvent(const AxisInput& input);

		/**
		 * Virtual function to query category of Event object
		 */
		virtual EventCategory GetEventCategory() const override;
		
		/** The Input being reported */
		AxisInput Input;
	};

}
