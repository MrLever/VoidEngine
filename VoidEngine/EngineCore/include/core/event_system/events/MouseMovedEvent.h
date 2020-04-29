#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "math/Vector.h"

#include "Event.h"

namespace core {
	class MouseMovedEvent : public Event {
		TYPE_INFO_DECL(MouseMovedEvent);

	public:
		/**
		 * The delta for mouse position
		 */
		math::Vector2 position;

		/**
		 * Constructor
		 */
		MouseMovedEvent(double xPos, double yPos);

		/**
		 * Virtual function to query category of Event object
		 */
		virtual EventCategory GetEventCategory() const override;

	};
}

