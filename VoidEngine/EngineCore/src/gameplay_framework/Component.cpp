//STD Headers

//Library Headers

//Void Engine Headers
#include "gameplay_framework/Component.h"

namespace core {

	Component::Component() : parent(nullptr), transform(nullptr) {

	}

	Component::~Component() {

	}

	Entity* Component::GetParent() {
		return parent;
	}

	void Component::Input(const InputAction& input, float deltaTime) {
		;
	}

	void Component::Input(const AxisInputAction& input, float deltaTime) {
		;
	}

	float Component::GetDistance(Component* other) const {
		return parent->GetDistance(other->GetParent());
	}

	float Component::GetDistanceSquared(Component* other) const {
		return parent->GetDistanceSquared(other->GetParent());
	}

	math::Vector3 Component::GetPosition() const {
		return parent->GetPosition();
	}

	void Component::Tick(float deltaTime) {
		;
	}

	void Component::Draw() {
		;
	}

}
