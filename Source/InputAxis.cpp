//STD Headers

//Library Headers


//Coati Headers
#include "InputAxis.h"


namespace EngineCore {

	InputAxis::InputAxis(){
		AxisValue = 0;
	}


	InputAxis::~InputAxis()	{

	}

	//Public Member Functions

	void InputAxis::AddBinding(KeyType input, double scale) {
		AxisBindings[input] = scale;
	}

	void InputAxis::UpdateAxis(const KeyboardInput &input)	{
		if (AxisBindings.find(input.GetKey()) == AxisBindings.end()) {
			return;
		}

		if (input.GetKeyState() == KeyState::Pressed) {
			AxisValue = AxisBindings[input.GetKey()];
		}
		else if (input.GetKeyState() == KeyState::Held) {
			;//Do not modify axis on hold
		}
		else if (input.GetKeyState() == KeyState::Released) {
			Reset();
		}
	}

	void InputAxis::Reset() {
		AxisValue = 0;
	}

	double InputAxis::Poll() const {
		return AxisValue;
	}

}