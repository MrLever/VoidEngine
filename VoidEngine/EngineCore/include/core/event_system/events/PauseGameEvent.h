#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/event_system/Event.h"

namespace core {

	class PauseGameEvent : public Event {
	public:
		TYPE_INFO_DECL(PauseGameEvent);
	};

}

