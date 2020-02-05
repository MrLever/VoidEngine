#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/event_system/events/Event.h"
#include "core/input/InputAction.h"

namespace core {
	class InputActionEvent : public Event {
	public:
		/**
		 * Constructor
		 */
		InputActionEvent(InputAction& action);

		/**
		 * Query type of Event object
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
		
		/** The Action being reported */
		InputAction Action;
	};
}

