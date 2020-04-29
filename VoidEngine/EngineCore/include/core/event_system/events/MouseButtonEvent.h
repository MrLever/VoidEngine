#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Event.h"
#include "input/definitions/MouseInput.h"

namespace core {
	class MouseButtonEvent : public Event {
		TYPE_INFO_DECL(MouseButtonEvent)

	public:
		/** The input this event is reporting */
		MouseInput Input;

		/**
		 * Constructor
		 */
		MouseButtonEvent(MouseInput& input);

		/**
		 * Virtual function to query category of Event object
		 */
		virtual EventCategory GetEventCategory() const override;

	};
}

