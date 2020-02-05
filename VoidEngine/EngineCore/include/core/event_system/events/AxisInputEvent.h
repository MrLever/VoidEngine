#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/event_system/events/Event.h"
#include "input/definitions/AxisInput.h"

namespace core {

	class AxisInputEvent : public Event {
	public:
		/**
		 * Constructor
		 */
		AxisInputEvent(const AxisInput& input);

		/**
		 * Function to query type of Event object
		 */
		virtual utils::Name GetEventType() const override;

		/**
		 * Virtual function to query category of Event object
		 */
		virtual EventCategory GetEventCategory() const override;

		/**
		 * Static function to get EventType info from C++ type info
		 */
		static utils::Name GetStaticEventType();
		
		/** The Input being reported */
		AxisInput Input;
	};

}
