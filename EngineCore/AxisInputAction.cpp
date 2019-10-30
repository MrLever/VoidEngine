//STD Headers

//Library Headers

//Void Engine Headers
#include "AxisInputAction.h"
#include "InputAxis.h"

namespace core {
	AxisInputAction::AxisInputAction(const utils::Name& name, float value) 
		: AxisName(name), Value(value) {
	
	}
	
	AxisInputAction::AxisInputAction(const std::string& name, float value)
		: AxisInputAction(utils::Name(name), value) {

	}

	bool AxisInputAction::operator==(const AxisInputAction& other) const {
		return AxisName == other.AxisName;
	}

}