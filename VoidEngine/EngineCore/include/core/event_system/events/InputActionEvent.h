#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/event_system/Event.h"
#include "core/input/InputAction.h"

namespace core {
	class InputActionEvent : public Event {
		ENABLE_RTTI(InputActionEvent)
	
	public:
		/** The Action being reported */
		InputAction action;

		/**
		 * Constructor
		 */
		InputActionEvent(InputAction& action);
		
	};
}

