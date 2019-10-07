#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Name.h"

namespace core {

	/**
	 * Structure to capture button and axis 
	 */
	struct InputEvent {
		utils::Name EventName;
		
		InputEvent(const std::string& name);
	};

}