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
		auto forward = Parent->GetRotation().ToVector();
		auto right = forward.Cross(EngineMath::Vector3(0, 1, 0)).Normalize();
		
		if (input.EventName == "Move Up") {
			Parent->SetPosition(
				Parent->GetPostion() + forward * speed
			);
		}
		else if (input.EventName == "Move Down") {
			Parent->SetPosition(
				Parent->GetPostion() - forward * speed
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

	void FlyingMovementComponent::Input(const InputAxis& axis, float deltaTime) {
		if (axis.AxisName == "MouseX") {
			auto newRotation = Parent->GetRotation();
			newRotation.Yaw += axis.Value;
			Parent->SetRotation(newRotation);
		}
		else if (axis.AxisName == "MouseY") {
			auto newRotation = Parent->GetRotation();
			newRotation.Pitch += axis.Value;
			if (newRotation.Pitch > 89.0f) {
				newRotation.Pitch = 89.0f;
			}
			if (newRotation.Pitch < -89.0f) {
				newRotation.Pitch = -89.0F;
			}
			Parent->SetRotation(newRotation);
		}
	}

	void FlyingMovementComponent::SetMoveSpeed(float speed) {
		MoveSpeed = speed;
	}

	float FlyingMovementComponent::GetMoveSpeed() {
		return MoveSpeed;
	}

}