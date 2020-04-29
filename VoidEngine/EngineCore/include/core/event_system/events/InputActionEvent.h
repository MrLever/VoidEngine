#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/event_system/events/Event.h"
#include "core/input/InputAction.h"

namespace core {
	class InputActionEvent : public Event {
		TYPE_INFO_DECL(InputActionEvent)
	
	public:
		/** The Action being reported */
		InputAction action;

		/**
		 * Constructor
		 */
		InputActionEvent(InputAction& action);
		
		/**
		 * Virtual function to query category of Event object
		 */
		virtual EventCategory GetEventCategory() const override;
	};
}

