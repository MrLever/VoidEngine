#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Name.h"

namespace core {
	
	enum class EventCategory : unsigned char {
		NONE = 0x00,
		RAW_INPUT = 0x01,
		INPUT = 0x02,
		WINDOW = 0x04
	};

	class Event {
	public:
	
		/**
		 * Virtual function to query type of Event object
		 */
		virtual utils::Name GetEventType() const = 0;

		/**
		 * Virtual function to query category of Event object
		 */
		virtual EventCategory GetEventCategory() const = 0;

		/**
		 * Static function to get EventType info from C++ type info
		 */
		static utils::Name GetStaticEventType();

		/** Boolean to determine if an event has been processed */
		bool IsHandled;
	};

}
