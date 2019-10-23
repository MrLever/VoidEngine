#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Event.h"

namespace core {
	class WindowCloseEvent : public Event {
	public:
		/**
		 * Function to query type of Event object
		 * @return "WindowCloseEvent"
		 */
		virtual utils::Name GetEventType() const;

		/**
		 * Function to query category of Event object
		 * @return EventCategory::Window
		 */
		virtual EventCategory GetEventCategory() const;

		/**
		 * Static function to get EventType info from C++ type info
		 * @return "WindowCloseEvent"
		 */
		static utils::Name GetStaticEventType();
	};
}

