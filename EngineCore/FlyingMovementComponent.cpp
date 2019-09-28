//STD Headers

//Library Headers

//Void Engine Headers
#include "FlyingMovementComponent.h"

namespace EngineCore {

	FlyingMovementComponent::FlyingMovementComponent(Entity* parent) 
		: Component(std::move(parent)), MoveSpeed(0.0f) {
	
	}

	void FlyingMovementComponent::Input(const InputEvent& input, float deltaTime) {
		
		auto speed = MoveSpeed * deltaTime;

		if (input.EventName == "Move Up") {
			Parent->SetPosition(
				Parent->GetPostion() + Parent->GetRotation().ToVector() * speed
			);
		}
		if (input.EventName == "Move Down") {
			Parent->SetPosition(
				Parent->GetPostion() - Parent->GetRotation().ToVector() * speed
			);
		}
	}

	void FlyingMovementComponent::SetMoveSpeed(float speed) {
		MoveSpeed = speed;
	}

	float FlyingMovementComponent::GetMoveSpeed() {
		return MoveSpeed;
	}

}