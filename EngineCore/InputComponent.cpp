//STD Headers

//Library Headers

//Void Engine Headers
#include "InputComponent.h"

namespace core {

	ENABLE_FACTORY(InputComponent, Component)

	InputComponent::InputComponent() {
	
	}

	void InputComponent::Initialize() {

	}

	void InputComponent::BindAction(const std::string& actionName, ActionType type, std::function<void(float)> callback) {
		InputAction action(actionName, type);
		ActionMappings.insert({ action, callback });
	}

	void InputComponent::BindAxis(const std::string& axisName, std::function<void(float, float)> callback) {
		AxisInputAction action(axisName, 0);
		AxisMappings.insert({ action, callback });
	}

	void InputComponent::Input(const InputAction& input, float deltaTime) {
		auto binding = ActionMappings.find(input);
		if (binding != ActionMappings.end()) {
			auto callback = binding->second;
			callback(deltaTime);
		}
	}

	void InputComponent::Input(const AxisInputAction& input, float deltaTime) {
		auto binding = AxisMappings.find(input);
		if (binding != AxisMappings.end()) {
			auto callback = binding->second;
			callback(input.Value, deltaTime);
		}
	}

	utils::Name InputComponent::GetTypename() const {
		return utils::Name(TypeName<InputComponent>::GetName());
	}

	utils::Name InputComponent::GetStaticTypename() {
		return utils::Name(TypeName<InputComponent>::GetName());
	}

}
