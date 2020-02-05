#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/event_system/events/Event.h"
#include "core/input/definitions/KeyboardInput.h"

namespace core {
	class KeyboardButtonEvent : public Event	{
	public:
		/**
		 * Constructor
		 */
		KeyboardButtonEvent(KeyboardInput& input);
		
		/**
		 * Virtual function to query type of Event object
		 */
		utils::Name GetEventType() const override;

		/**
		 * Virtual function to query category of Event object
		 */
		virtual EventCategory GetEventCategory() const override;

		/**
		 * Static function to get EventType info from C++ type info
		 */
		static utils::Name GetStaticEventType() /** override */;

		/** The input this event is reporting */
		KeyboardInput Input;
	};
}

