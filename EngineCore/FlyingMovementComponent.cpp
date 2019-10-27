//STD Headers

//Library Headers

//Void Engine Headers
#include "FlyingMovementComponent.h"

namespace core {

	FlyingMovementComponent::FlyingMovementComponent(Entity* parent) 
		: MovementComponent(std::move(parent)) {
	
	}

	void FlyingMovementComponent::Input(const InputAction& input, float deltaTime) {
		

	}

	void FlyingMovementComponent::Input(const InputAxisReport& axis, float deltaTime) {
		if (axis.AxisName == "LookRight") {
			auto newRotation = Parent->GetRotation();
			newRotation.Yaw += axis.Value;
			Parent->SetRotation(newRotation);
		}
		else if (axis.AxisName == "LookUp") {
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
		auto speed = MoveSpeed * deltaTime;
		auto forward = Parent->GetRotation().ToVector();
		auto right = forward.Cross(math::Vector3(0, 1, 0)).Normalize();

		if (axis.AxisName == "UpAxis") {
			Parent->SetPosition(
				Parent->GetPostion() + forward * axis.Value * speed
			);
		}
		else if (axis.AxisName == "RightAxis") {
			Parent->SetPosition(
				Parent->GetPostion() + right * axis.Value * speed
			);
		}
	}

}