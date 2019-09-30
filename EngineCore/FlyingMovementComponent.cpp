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
		auto right = EngineMath::Vector3(0, 0, -1).Cross(EngineMath::Vector3(0, 1, 0)).Normalize();
		if (input.EventName == "Move Up") {
			Parent->SetPosition(
				Parent->GetPostion() + EngineMath::Vector3(0,0,-1) * speed
			);
		}
		else if (input.EventName == "Move Down") {
			Parent->SetPosition(
				Parent->GetPostion() - EngineMath::Vector3(0, 0, -1) * speed
			);
		}
		else if (input.EventName == "Move Left") {
			Parent->SetPosition(
				Parent->GetPostion() - right * speed
			);
		}
		else if (input.EventName == "Move Right") {
			Parent->SetPosition(
				Parent->GetPostion() + right * speed
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