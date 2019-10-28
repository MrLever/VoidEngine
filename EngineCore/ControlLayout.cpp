//STD Headers

//Library Headers

//Void Engine Headers
#include "ControlLayout.h"

namespace core {

	ControlLayout::ControlLayout(const std::string& filePath) : JsonResource(filePath) {

	}

	void ControlLayout::Initialize() {
		LoadActionMappings();
		
		LoadAxisMappings();
	}

	void ControlLayout::UpdateAxis(AxisInputAction update) {
		auto axisIter = InputAxes.find(update.AxisName);
		if (axisIter != InputAxes.end()) {
			auto axis = axisIter->second;
			if (axis) {
				axis->UpdateAxis(update.Value);
			}
		}
	}

	AxisInputAction ControlLayout::PollAxis(const utils::Name& axisName) {
		auto axisIter = InputAxes.find(axisName);
		if (axisIter != InputAxes.end()) {
			auto axis = axisIter->second;
			if (axis) {
				return AxisInputAction(axisName, axis->Poll());
			}
		}
		else {
			utils::Logger::LogError("Control Layout does not have axis " + axisName.StringID + ". Polling failed");
			return AxisInputAction("ERROR", 0);
		}
	}

	void ControlLayout::LoadActionMappings() {
		auto actionMappings = Data["actionMappings"];
		for (auto mapping : actionMappings) {
			if (mapping.find("key") != mapping.end()) {
				KeyboardActionBindings.insert(
					{
						DeserializeKB(mapping["key"], mapping["modifiers"]), 
						utils::Name(mapping["action"])
					}
				);
			}
			else if (mapping.find("gamepadButton") != mapping.end()) {
				GamepadActionBindings.insert(
					{
						DeserializeGamepadButton(mapping["gamepadButton"], mapping["modifiers"]), 
						utils::Name(mapping["action"])
					}
				);
			}
			else if (mapping.find("mouseButton") != mapping.end()) {
				GamepadActionBindings.insert(
					{
						DeserializeGamepadButton(mapping["mouseButton"], mapping["modifiers"]),
						utils::Name(mapping["action"])
					}
				);
			}
		}
	}

	void ControlLayout::LoadAxisMappings() {
		auto axisMappings = Data["axisMappings"];
		for (auto& mapping : axisMappings) {
			utils::Name currentAxis(mapping["axisName"]);

			InputAxes[currentAxis] = std::make_shared<InputAxis>(currentAxis);

			auto bindings = mapping["bindings"];
			for (auto& binding : bindings) {
				if (binding.find("key") != binding.end()) {
					auto key = DeserializeKB(binding["key"], std::vector<std::string>());
					std::pair axisEffect(currentAxis, binding["value"]);
					KeyboardAxisBindings.insert({ key, axisEffect });
				}
				else if (binding.find("gamepadButton") != binding.end()) {
					auto key = DeserializeGamepadButton(binding["key"], std::vector<std::string>());
					std::pair axisEffect(currentAxis, binding["value"]);
					GamepadAxisBindings.insert({ key, axisEffect });
				}
				else if (binding.find("mouseButton") != binding.end()) {
					auto key = DeserializeMouseButton(binding["key"], std::vector<std::string>());
					std::pair axisEffect(currentAxis, binding["value"]);
					MouseAxisBindings.insert({ key, axisEffect });
				}
				else if (binding.find("axis") != binding.end()) {
					auto rawAxis = DeserializeRawAxis(binding["axis"]);
					std::pair axisEffect(currentAxis, binding["value"]);
					AnalogAxisBindings.insert({ rawAxis, axisEffect });
				}
			}
		}
	}

	InputAction ControlLayout::GetActionMapping(const KeyboardInput& input) const {
		ActionType type = (input.GetButtonState() == ButtonState::PRESSED) ? 
			ActionType::PRESSED : ActionType::RELEASED;

		auto binding = KeyboardActionBindings.find(input.GetButton());
		if (binding == KeyboardActionBindings.end()) {
			return InputAction("Error", type);
		}

		return InputAction(binding->second, type);
	}

	InputAction ControlLayout::GetActionMapping(const MouseInput& input) const {
		ActionType type = (input.GetButtonState() == ButtonState::PRESSED) ?
			ActionType::PRESSED : ActionType::RELEASED;

		auto binding = MouseActionBindings.find(input.GetButton());
		if (binding == MouseActionBindings.end()) {
			return InputAction("Error", type);
		}

		return InputAction(binding->second, type);
	}

	InputAction ControlLayout::GetActionMapping(const GamepadInput& input) const {
		ActionType type = (input.GetButtonState() == ButtonState::PRESSED) ?
			ActionType::PRESSED : ActionType::RELEASED;

		auto binding = GamepadActionBindings.find(input.GetButton());
		if (binding == GamepadActionBindings.end()) {
			return InputAction("Error", type);
		}

		return InputAction(binding->second, type);
	}

	InputAction ControlLayout::GetActionMapping(const AxisInput& input) const {
		return InputAction("Error", ActionType::PRESSED);
	}

	AxisInputAction ControlLayout::GetAxisMapping(const KeyboardInput& input) const {
		auto binding = KeyboardAxisBindings.find(input.GetButton());
		if (binding == KeyboardAxisBindings.end()) {
			return AxisInputAction("Error", 0);
		}

		auto axisName = binding->second.first;
		auto axisValue = binding->second.second;

		if (input.GetButtonState() == ButtonState::RELEASED) {
			axisValue *= -1;
		}

		return AxisInputAction(axisName, axisValue);
	}

	AxisInputAction ControlLayout::GetAxisMapping(const MouseInput& input) const {
		auto binding = MouseAxisBindings.find(input.GetButton());
		if (binding == MouseAxisBindings.end()) {
			return AxisInputAction("Error", 0);
		}

		auto axisName = binding->second.first;
		auto axisValue = binding->second.second;

		if (input.GetButtonState() == ButtonState::RELEASED) {
			axisValue *= -1;
		}

		return AxisInputAction(axisName, axisValue);
	}

	AxisInputAction ControlLayout::GetAxisMapping(const GamepadInput& input) const {
		auto binding = GamepadAxisBindings.find(input.GetButton());
		if (binding == GamepadAxisBindings.end()) {
			return AxisInputAction("Error", 0);
		}

		auto axisName = binding->second.first;
		auto axisValue = binding->second.second;

		if (input.GetButtonState() == ButtonState::RELEASED) {
			axisValue *= -1;
		}

		return AxisInputAction(axisName, axisValue);
	}

	AxisInputAction ControlLayout::GetAxisMapping(const AxisInput& input) const {
		auto binding = AnalogAxisBindings.find(input.GetAxisSource());
		if (binding == AnalogAxisBindings.end()) {
			return AxisInputAction("Error", 0);
		}

		return AxisInputAction(binding->second.first, input.GetAxisValue() * binding->second.second);
	}

	bool ControlLayout::IsBound(const KeyboardInput& input) const {
		return
			KeyboardActionBindings.find(input.GetButton()) != KeyboardActionBindings.end()
			|| KeyboardAxisBindings.find(input.GetButton()) != KeyboardAxisBindings.end();
	}

	bool ControlLayout::IsBound(const MouseInput& input) const{
		return 
			MouseActionBindings.find(input.GetButton()) != MouseActionBindings.end()
			|| MouseAxisBindings.find(input.GetButton()) != MouseAxisBindings.end();
	}

	bool ControlLayout::IsBound(const GamepadInput& input) const {
		return
			GamepadActionBindings.find(input.GetButton()) != GamepadActionBindings.end()
			|| GamepadAxisBindings.find(input.GetButton()) != GamepadAxisBindings.end();
	}

	bool ControlLayout::IsBound(const AxisInput& input) const{
		return AnalogAxisBindings.find(input.GetAxisSource()) != AnalogAxisBindings.end();
	}

	bool ControlLayout::IsBoundToAction(const KeyboardInput& input) const {
		return KeyboardActionBindings.find(input.GetButton()) != KeyboardActionBindings.end();
	}

	bool ControlLayout::IsBoundToAction(const MouseInput& input) const {
		return MouseActionBindings.find(input.GetButton()) != MouseActionBindings.end();
	}

	bool ControlLayout::IsBoundToAction(const GamepadInput& input) const {
		return GamepadActionBindings.find(input.GetButton()) != GamepadActionBindings.end();
	}

	bool ControlLayout::IsBoundToAction(const AxisInput& input) const {
		return false;
	}

	bool ControlLayout::IsBoundToAxis(const KeyboardInput& input) const {
		return KeyboardAxisBindings.find(input.GetButton()) != KeyboardAxisBindings.end();
	}

	bool ControlLayout::IsBoundToAxis(const MouseInput& input) const {
		return MouseAxisBindings.find(input.GetButton()) != MouseAxisBindings.end();
	}

	bool ControlLayout::IsBoundToAxis(const GamepadInput& input) const {
		return GamepadAxisBindings.find(input.GetButton()) != GamepadAxisBindings.end();
	}

	bool ControlLayout::IsBoundToAxis(const AxisInput& input) const {
		return AnalogAxisBindings.find(input.GetAxisSource()) != AnalogAxisBindings.end();
	}

}
