//STD Headers

//Library Headers

//Void Engine Headers
#include "Component.h"

namespace core {
	Component::Component() {
		Parent = nullptr;
	}

	void Component::SetParent(Entity* parent) {
		Parent = parent;
	}

	void Component::SetConfigData(const nlohmann::json& data) {
		ComponentData = data;
	}

	void Component::Input(const InputAction& input, float deltaTime) {
		;
	}

	void Component::Input(const AxisInputAction& input, float deltaTime) {
		;
	}

	void Component::Tick(float deltaTime) {
		;
	}

	void Component::Draw() {
		;
	}

	void Component::SetPosition(const math::Vector3& position) {
		Position = position;
	}

	math::Vector3 Component::GetPosition() const {
		return Position;
	}

	void Component::SetRotation(const math::Rotator& rotation) {
		Rotation = rotation;
	}

	utils::Name Component::GetStaticTypename() {
		return utils::Name(TypeName<Component>::GetName());
	}
}
