//STD Headers

//Library Headers

//Void Engine Headers
#include "input/components/InputComponent.h"

namespace core {

	ENABLE_FACTORY(InputComponent, Component)

	InputComponent::InputComponent() {
	
	}

	void InputComponent::Initialize() {

	}

	void InputComponent::BindAction(const std::string& actionName, ActionType type, std::function<void(float)> callback) {
		InputAction action(actionName, type);
		m_ActionMappings.insert({ action, callback });
	}

	void InputComponent::BindAxis(const std::string& axisName, std::function<void(float, float)> callback) {
		AxisInputAction action(axisName, 0);
		m_AxisMappings.insert({ action, callback });
	}

	void InputComponent::Input(const InputAction& input, float deltaTime) {
		auto binding = m_ActionMappings.find(input);
		if (binding != m_ActionMappings.end()) {
			auto callback = binding->second;
			callback(deltaTime);
		}
	}

	void InputComponent::Input(const AxisInputAction& input, float deltaTime) {
		auto binding = m_AxisMappings.find(input);
		if (binding != m_AxisMappings.end()) {
			auto callback = binding->second;
			callback(input.Value, deltaTime);
		}
	}

}
