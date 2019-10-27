//STD Headers

//Library Headers

//Void Engine Headers
#include "InputAxisAction.h"
#include "InputAxis.h"

namespace core {
	InputAxisAction::InputAxisAction(const utils::Name& name, float value) 
		: AxisName(name), Value(value) {
	
	}
	
	InputAxisAction::InputAxisAction(const std::string& name, float value)
		: InputAxisAction(utils::Name(name), value) {

	}

	bool InputAxisAction::operator==(const InputAxisAction& other) const {
		return AxisName == other.AxisName;
	}

}