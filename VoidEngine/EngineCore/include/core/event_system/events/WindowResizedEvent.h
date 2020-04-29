#pragma once
#include "Event.h"
namespace core{
	class WindowResizedEvent : public Event {
		TYPE_INFO_DECL(WindowResizedEvent)
	
	public:
		/** The width the window was resized to */
		int width;

		/** The height the window was resized to */
		int height;

		/**
		 * Constructor
		 */
		WindowResizedEvent(int width, int height);

		virtual EventCategory GetEventCategory() const override;

	};
}

