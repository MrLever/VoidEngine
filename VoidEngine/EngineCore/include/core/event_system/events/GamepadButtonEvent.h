#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/event_system/Event.h"
#include "core/input/definitions/GamepadInput.h"

namespace core {

	class GamepadButtonEvent : public Event {
		ENABLE_RTTI(GamepadButtonEvent)
	public:
		/** Input being reported by this event */
		GamepadInput Input;

		/**
		 * Constructor
		 */
		GamepadButtonEvent(const GamepadInput& input);
	};

}

