#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Name.h"

namespace EngineCore {

	/**
	 * Structure to capture button and axis 
	 */
	struct InputEvent {
		EngineUtils::Name EventName;
		
		InputEvent(const std::string& name);
	};

}