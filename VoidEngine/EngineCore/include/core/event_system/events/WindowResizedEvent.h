#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/event_system/Event.h"

namespace core{
	class WindowResizedEvent : public Event {
		ENABLE_RTTI(WindowResizedEvent)
	
	public:
		/** The width the window was resized to */
		int width;

		/** The height the window was resized to */
		int height;

		/**
		 * Constructor
		 */
		WindowResizedEvent(int width, int height);
	};
}

