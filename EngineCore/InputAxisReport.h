#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Name.h"

namespace core {

	struct InputAxisReport {
		utils::Name AxisName;
		float Value;

		/**
		 * Constructor
		 * @param name The axis' name
		 * @param value The axis' reading
		 */
		InputAxisReport(const std::string& name, float value);
	};

}