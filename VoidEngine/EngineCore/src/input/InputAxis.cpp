//STD Headers

//Library Headers

//Void Engine Headers
#include "InputAxis.h"

namespace core {

	InputAxis::InputAxis(const std::string& name) : AxisName(name), Value(0) {
	
	}

	InputAxis::InputAxis(const utils::Name& name) : AxisName(name), Value(0) {
	}

	void InputAxis::UpdateAxis(float value) {
		Value += value;
	}

	float InputAxis::Poll() const {
		return Value;
	}

	utils::Name InputAxis::GetAxisName() const {
		return AxisName;
	}

	bool InputAxis::operator==(const InputAxis& other) const {
		return AxisName == other.AxisName;
	}

}