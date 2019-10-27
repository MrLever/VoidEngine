#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Name.h"

namespace core {

	/**
	 * @struct InputEvent
	 * @brief Struct to deliver input action data to entities
	 */
	struct InputEvent {
		utils::Name EventName;
		
		InputEvent(const std::string& name);
	};

}