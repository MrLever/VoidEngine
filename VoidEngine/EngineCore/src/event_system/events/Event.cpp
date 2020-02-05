//STD Headers

//Library Headers

//Void Engine Headers
#include "event_system/events/Event.h"

namespace core {
	Event::Event() : IsHandled(false) {
	
	}

	utils::Name Event::GetStaticEventType() {
		return utils::Name("ERROR");
	}

}