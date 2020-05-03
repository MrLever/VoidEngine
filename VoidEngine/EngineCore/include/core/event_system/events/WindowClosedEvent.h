#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/event_system/Event.h"

namespace core {
	class WindowClosedEvent : public Event {
		TYPE_INFO_DECL(WindowClosedEvent)
	public:
		/**
		 * Constructor
		 */
		WindowClosedEvent() = default;
	};
}

