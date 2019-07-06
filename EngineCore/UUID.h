#pragma once
//STD Headers
#include <string>

//Library Headers

//Void Engine Headers
#include "EngineUtilities.h"

struct UUID {
	/**
	 * Constructor
	 * @param id The string from which the UUID is generated.
	 */
	UUID(std::string id);



	std::string stringID;
	unsigned long long ID;
};