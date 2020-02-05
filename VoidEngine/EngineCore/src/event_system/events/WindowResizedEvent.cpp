//STD Headers

//Library Headers

//Void Engine Headers
#include "event_system/events/WindowResizedEvent.h"

namespace core {
	WindowResizedEvent::WindowResizedEvent(int width, int height) 
		: Width(width), Height(height) {
	
	}
	
	utils::Name WindowResizedEvent::GetEventType() const {
		return utils::Name("WindowResizedEvent");
	}

	EventCategory WindowResizedEvent::GetEventCategory() const {
		return EventCategory::WINDOW;
	}

	utils::Name WindowResizedEvent::GetStaticEventType() {
		return utils::Name("WindowResizedEvent");
	}

	int WindowResizedEvent::GetWidth() {
		return Width;
	}

	int WindowResizedEvent::GetHeight() {
		return Height;
	}

}