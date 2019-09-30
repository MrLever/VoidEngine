#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Name.h"

namespace EngineCore {

	struct InputAxis {
		EngineUtils::Name AxisName;
		float Value;

		/**
		 * Constructor
		 * @param name The axis' name
		 * @param value The axis' reading
		 */
		InputAxis(const std::string& name, float value);
	};

}