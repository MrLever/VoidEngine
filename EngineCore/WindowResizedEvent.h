#pragma once
#include "Event.h"
namespace core{
	class WindowResizedEvent : public Event {
	public:
		/**
		 * Constructor
		 */
		WindowResizedEvent(int width, int height);


		utils::Name GetEventType() const override;

		virtual EventCategory GetEventCategory() const override;

		static utils::Name GetStaticEventType() /** override */;

		/**
		 * Function to access the new window width
		 * @return Width
		 */
		int GetWidth();

		/**
		 * Function to access the new window height
		 * @return Height
		 */
		int GetHeight();

	private:
		/** The width the window was resized to */
		int Width;

		/** The height the window was resized to */
		int Height;
	};
}

