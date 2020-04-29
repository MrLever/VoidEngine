#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/event_system/events/Event.h"
#include "core/input/definitions/KeyboardInput.h"

namespace core {
	class KeyboardButtonEvent : public Event {
		TYPE_INFO_DECL(KeyboardButtonEvent)

	public:
		/** The input this event is reporting */
		KeyboardInput input;

		/**
		 * Constructor
		 */
		KeyboardButtonEvent(KeyboardInput& input);

		/**
		 * Virtual function to query category of Event object
		 */
		virtual EventCategory GetEventCategory() const override;

	};
}

