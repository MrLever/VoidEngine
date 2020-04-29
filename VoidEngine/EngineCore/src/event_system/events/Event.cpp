//STD Headers

//Library Headers

//Void Engine Headers
#include "event_system/events/Event.h"

namespace core {

	TYPE_INFO_IMPL(Event)

	Event::Event() : eventHandled(false) {
	
	}

	EventID Event::GetID() const {
		return GetTypename().ID;
	}


}