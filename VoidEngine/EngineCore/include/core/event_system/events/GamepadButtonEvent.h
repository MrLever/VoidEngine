#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/event_system/events/Event.h"
#include "core/input/definitions/GamepadInput.h"

namespace core {

	class GamepadButtonEvent : public Event {
	public:
		/**
		 * Constructor
		 */
		GamepadButtonEvent(const GamepadInput& input);

		/**
		 * Virtual function to query type of Event object
		 */
		virtual utils::Name GetEventType() const;

		/**
		 * Virtual function to query category of Event object
		 */
		virtual EventCategory GetEventCategory() const;

		/**
		 * Static function to get EventType info from C++ type info
		 */
		static utils::Name GetStaticEventType();
	
		/** Input being reported by this event */
		GamepadInput Input;
	};

}

