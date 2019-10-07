//STD Headers

//Libarary Headers

//Void Engine Headers
#include "MovementComponent.h"

namespace core {

	MovementComponent::MovementComponent(Entity* parent) : Component(parent), MoveSpeed(0) {

	}

	void MovementComponent::SetMoveSpeed(float speed) {
		MoveSpeed = speed;
	}

	float MovementComponent::GetMoveSpeed() {
		return MoveSpeed;
	}
}
