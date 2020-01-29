#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "math/Vector.h"

#include "Event.h"

namespace core {
	class MouseMovedEvent : public Event {
	public:
		/**
		 * Constructor
		 */
		MouseMovedEvent(double xPos, double yPos);

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

		/**
		 * The delta for mouse position
		 */
		math::Vector2 Position;
	};
}

