//STD Headers

//Library Headers

//Void Engine Headers
#include "event_system/events/WindowResizedEvent.h"

namespace core {

	TYPE_INFO_IMPL(WindowResizedEvent)

	WindowResizedEvent::WindowResizedEvent(int width, int height) 
		: width(width), height(height) {
	
	}
	
}