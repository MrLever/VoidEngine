//STD Headers

//Library Headers

//Void Engine Headers
#include "Component.h"

namespace core {
	Component::Component(Entity* parent) 
		: Parent(parent), Position(parent->GetPostion()), Rotation(parent->GetRotation()) {

	}

	void Component::Input(const InputAction& input, float deltaTime) {
		;
	}

	void Component::Input(const InputAxisReport& input, float deltaTime) {

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

	void Component::SetRotation(const math::Rotator& rotation) {
		Rotation = rotation;
	}
}
