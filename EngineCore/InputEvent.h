#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Name.h"

namespace EngineCore {

	struct InputEvent {
		EngineUtils::Name EventName;

		InputEvent(const std::string& name);
	};

}