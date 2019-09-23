//STD Headers

//Library Headers

//Void Engine Headers
#include "Component.h"

namespace EngineCore {
	Component::Component(Entity* parent) : Parent(parent) {

	}

	void Component::Input(const KeyboardInput& input) {
		;
	}

	void Component::Input(const MouseInput& input) {
		;
	}

	void Component::Input(const GamepadInput& input) {
		;
	}

	void Component::Tick(float deltaTime) {
		;
	}

	void Component::Draw() {
		;
	}

	void Component::SetPosition(const EngineMath::Vector3& position) {
		Position = position;
	}

	void Component::SetRotation(const EngineMath::Rotator& rotation) {
		Rotation = rotation;
	}
}
