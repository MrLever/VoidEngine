//STD Headers

//Library Headers

//Void Engine Headers
#include "input/ControlLayout.h"

namespace core {

	ControlLayout::ControlLayout(const std::string& filePath) : JsonResource(filePath) {

	}

	void ControlLayout::Initialize() {
		LoadActionMappings();
		
		LoadAxisMappings();
	}

	void ControlLayout::UpdateAxis(AxisInputAction update) {
		auto axisIter = m_InputAxes.find(update.AxisName);
		if (axisIter != m_InputAxes.end()) {
			auto axis = axisIter->second;
			if (axis) {
				axis->UpdateAxis(update.Value);
			}
		}
	}

	std::vector<AxisInputAction> ControlLayout::PollAxes() {
		std::vector<AxisInputAction> readings;

		for (auto axisIter : m_InputAxes) {
			readings.emplace_back(PollAxis(axisIter.first));
		}

		return readings;
	}

	AxisInputAction ControlLayout::PollAxis(const utils::Name& axisName) {
		auto axisIter = m_InputAxes.find(axisName);
		if (axisIter != m_InputAxes.end()) {
			auto axis = axisIter->second;
			if (axis) {
				return AxisInputAction(axisName, axis->Poll());
			}
		}

		utils::Logger::LogError("Control Layout does not have axis " + axisName.StringID + ". Polling failed");
		return AxisInputAction("ERROR", 0);
	}

	void ControlLayout::LoadActionMappings() {
		auto actionMappings = Data["actionMappings"];
		for (auto mapping : actionMappings) {
			if (mapping.find("key") != mapping.end()) {
				m_KeyboardActionBindings.insert(
					{
						DeserializeKB(mapping["key"], mapping["modifiers"]), 
						utils::Name(mapping["action"])
					}
				);
			}
			else if (mapping.find("gamepadButton") != mapping.end()) {
				m_GamepadActionBindings.insert(
					{
						DeserializeGamepadButton(mapping["gamepadButton"], mapping["modifiers"]), 
						utils::Name(mapping["action"])
					}
				);
			}
			else if (mapping.find("mouseButton") != mapping.end()) {
				m_MouseActionBindings.insert(
					{
						DeserializeMouseButton(mapping["mouseButton"], mapping["modifiers"]),
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

			m_InputAxes[currentAxis] = std::make_shared<InputAxis>(currentAxis);

			auto bindings = mapping["bindings"];
			for (auto& binding : bindings) {
				if (binding.find("key") != binding.end()) {
					auto key = DeserializeKB(binding["key"], std::vector<std::string>());
					std::pair axisEffect(currentAxis, binding["value"]);
					m_KeyboardAxisBindings.insert({ key, axisEffect });
				}
				else if (binding.find("gamepadButton") != binding.end()) {
					auto key = DeserializeGamepadButton(binding["key"], std::vector<std::string>());
					std::pair axisEffect(currentAxis, binding["value"]);
					m_GamepadAxisBindings.insert({ key, axisEffect });
				}
				else if (binding.find("mouseButton") != binding.end()) {
					auto key = DeserializeMouseButton(binding["key"], std::vector<std::string>());
					std::pair axisEffect(currentAxis, binding["value"]);
					m_MouseAxisBindings.insert({ key, axisEffect });
				}
				else if (binding.find("axis") != binding.end()) {
					auto rawAxis = DeserializeRawAxis(binding["axis"]);
					std::pair axisEffect(currentAxis, binding["value"]);
					m_AnalogAxisBindings.insert({ rawAxis, axisEffect });
				}
			}
		}
	}

	InputAction ControlLayout::GetActionMapping(const KeyboardInput& input) const {
		ActionType type = (input.GetButtonState() == ButtonState::PRESSED) ? 
			ActionType::PRESSED : ActionType::RELEASED;

		auto binding = m_KeyboardActionBindings.find(input.GetButton());
		if (binding == m_KeyboardActionBindings.end()) {
			return InputAction("Error", type);
		}

		return InputAction(binding->second, type);
	}

	InputAction ControlLayout::GetActionMapping(const MouseInput& input) const {
		ActionType type = (input.GetButtonState() == ButtonState::PRESSED) ?
			ActionType::PRESSED : ActionType::RELEASED;

		auto binding = m_MouseActionBindings.find(input.GetButton());
		if (binding == m_MouseActionBindings.end()) {
			return InputAction("Error", type);
		}

		return InputAction(binding->second, type);
	}

	InputAction ControlLayout::GetActionMapping(const GamepadInput& input) const {
		ActionType type = (input.GetButtonState() == ButtonState::PRESSED) ?
			ActionType::PRESSED : ActionType::RELEASED;

		auto binding = m_GamepadActionBindings.find(input.GetButton());
		if (binding == m_GamepadActionBindings.end()) {
			return InputAction("Error", type);
		}

		return InputAction(binding->second, type);
	}

	InputAction ControlLayout::GetActionMapping(const AxisInput& input) const {
		return InputAction("Error", ActionType::PRESSED);
	}

	AxisInputAction ControlLayout::GetAxisMapping(const KeyboardInput& input) const {
		auto binding = m_KeyboardAxisBindings.find(input.GetButton());
		if (binding == m_KeyboardAxisBindings.end()) {
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
		auto binding = m_MouseAxisBindings.find(input.GetButton());
		if (binding == m_MouseAxisBindings.end()) {
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
		auto binding = m_GamepadAxisBindings.find(input.GetButton());
		if (binding == m_GamepadAxisBindings.end()) {
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
		auto binding = m_AnalogAxisBindings.find(input.GetAxisSource());
		if (binding == m_AnalogAxisBindings.end()) {
			return AxisInputAction("Error", 0);
		}

		return AxisInputAction(binding->second.first, input.GetAxisValue() * binding->second.second);
	}

	bool ControlLayout::IsBound(const KeyboardInput& input) const {
		return
			m_KeyboardActionBindings.find(input.GetButton()) != m_KeyboardActionBindings.end()
			|| m_KeyboardAxisBindings.find(input.GetButton()) != m_KeyboardAxisBindings.end();
	}

	bool ControlLayout::IsBound(const MouseInput& input) const{
		return 
			m_MouseActionBindings.find(input.GetButton()) != m_MouseActionBindings.end()
			|| m_MouseAxisBindings.find(input.GetButton()) != m_MouseAxisBindings.end();
	}

	bool ControlLayout::IsBound(const GamepadInput& input) const {
		return
			m_GamepadActionBindings.find(input.GetButton()) != m_GamepadActionBindings.end()
			|| m_GamepadAxisBindings.find(input.GetButton()) != m_GamepadAxisBindings.end();
	}

	bool ControlLayout::IsBound(const AxisInput& input) const{
		return m_AnalogAxisBindings.find(input.GetAxisSource()) != m_AnalogAxisBindings.end();
	}

	bool ControlLayout::IsBoundToAction(const KeyboardInput& input) const {
		return m_KeyboardActionBindings.find(input.GetButton()) != m_KeyboardActionBindings.end();
	}

	bool ControlLayout::IsBoundToAction(const MouseInput& input) const {
		return m_MouseActionBindings.find(input.GetButton()) != m_MouseActionBindings.end();
	}

	bool ControlLayout::IsBoundToAction(const GamepadInput& input) const {
		return m_GamepadActionBindings.find(input.GetButton()) != m_GamepadActionBindings.end();
	}

	bool ControlLayout::IsBoundToAction(const AxisInput& input) const {
		return false;
	}

	bool ControlLayout::IsBoundToAxis(const KeyboardInput& input) const {
		return m_KeyboardAxisBindings.find(input.GetButton()) != m_KeyboardAxisBindings.end();
	}

	bool ControlLayout::IsBoundToAxis(const MouseInput& input) const {
		return m_MouseAxisBindings.find(input.GetButton()) != m_MouseAxisBindings.end();
	}

	bool ControlLayout::IsBoundToAxis(const GamepadInput& input) const {
		return m_GamepadAxisBindings.find(input.GetButton()) != m_GamepadAxisBindings.end();
	}

	bool ControlLayout::IsBoundToAxis(const AxisInput& input) const {
		return m_AnalogAxisBindings.find(input.GetAxisSource()) != m_AnalogAxisBindings.end();
	}

}
