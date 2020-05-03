#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/event_system/Event.h"

namespace core {

	class PauseGameEvent : public Event {
	public:
		/**
		 * Function to query type of Event object
		 * @return "WindowClosedEvent"
		 */
		virtual utils::Name GetEventType() const;

		/**
		 * Function to query category of Event object
		 * @return EventCategory::Window
		 */
		virtual EventCategory GetEventCategory() const;

		/**
		 * Static function to get EventType info from C++ type info
		 * @return "WindowClosedEvent"
		 */
		static utils::Name GetStaticEventType();

	};

}

