//STD Headers

//Library Headers

//Void Engine Headers
#include "AxisInput.h"

namespace core {

	AxisInput::AxisInput(RawAxisType axis, float value) : Axis(axis), AxisValue(value) {
	
	}

	RawAxisType AxisInput::GetAxisSource() const {
		return Axis;
	}

	float AxisInput::GetAxisValue() const {
		return AxisValue;
	}

	bool AxisInput::operator==(const AxisInput& other) const {
		return Axis == other.Axis;
	}
}