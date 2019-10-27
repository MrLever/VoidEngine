#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Name.h"

namespace core {

	/**
	 * @struct InputAction
	 * @brief Struct to deliver input action data to entities
	 */
	struct InputAction {
		utils::Name EventName;
		
		InputAction(const std::string& name);
	};

}