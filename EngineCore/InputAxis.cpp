//STD Headers

//Library Headers

//Void Engine Headers
#include "InputAxis.h"

namespace core {

	InputAxis::InputAxis(const std::string& name) : AxisName(name), Value(0) {
	
	}

	InputAxis::InputAxis(const utils::Name& name) : AxisName(name), Value(0) {
	}

	void InputAxis::UpdateAxis(const KeyboardInput& input) {
		if (Keybindings.find(input) == Keybindings.end()) {
			return;
		}

		Value += Keybindings[input];
	}

	float InputAxis::Poll() const {
		return Value;
	}

	void InputAxis::AddBinding(const KeyboardInput& input, float value) {
		Keybindings[input] = value;
		if (input.GetButtonState() == ButtonState::PRESSED) {
			Keybindings[KeyboardInput(input.GetButton(), ButtonState::RELEASED)] = -1 * value;
		}
		else if(input.GetButtonState() == ButtonState::RELEASED) {
			Keybindings[KeyboardInput(input.GetButton(), ButtonState::PRESSED)] = -1 * value;
		}
	}

	void InputAxis::RemoveBinding(const KeyboardInput& input) {
		Keybindings.erase(input);
	}

	utils::Name InputAxis::GetAxisName() const {
		return AxisName;
	}

	bool InputAxis::operator==(const InputAxis& other) const {
		return AxisName == other.AxisName;
	}

}