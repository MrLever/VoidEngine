#include "Event.h"

namespace core {
	Event::Event() : IsHandled(false) {
	
	}

	utils::Name Event::GetStaticEventType() {
		return utils::Name("ERROR");
	}

}