//STD Headers

//Library Headers

//Void Engine Headers
#include "gameplay_framework/Component.h"

namespace core {

	TYPE_INFO_IMPL(Component)

	Component::Component() : m_Parent(nullptr), m_Transform(nullptr) {

	}

	Component::~Component() {

	}

	Entity* Component::GetParent() {
		return m_Parent;
	}

	void Component::Input(const InputAction& input, float deltaTime) {
		;
	}

	void Component::Input(const AxisInputAction& input, float deltaTime) {
		;
	}

	float Component::GetDistance(Component* other) const {
		return m_Parent->GetDistance(other->GetParent());
	}

	float Component::GetDistanceSquared(Component* other) const {
		return m_Parent->GetDistanceSquared(other->GetParent());
	}

	math::Vector3 Component::GetPosition() const {
		return m_Parent->GetPostion();
	}

	void Component::Tick(float deltaTime) {
		;
	}

	void Component::Draw() {
		;
	}

}
