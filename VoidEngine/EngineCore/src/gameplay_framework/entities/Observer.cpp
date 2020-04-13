//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/factory/Factory.h"
#include "utils/Logger.h"

#include "gameplay_framework/entities/Observer.h"
#include "rendering/Components/CameraComponent.h"

namespace core {

	TYPE_INFO_IMPL(Observer)

	ENABLE_FACTORY(Observer, Entity)
	
	Observer::Observer() {

	}

	Observer::~Observer() {

	}

	void Observer::Initialize() {
		PlayerEntity::Initialize();

		MovementSpeed = 10;
	}

	void Observer::BeginPlay() {
		utils::Logger::LogInfo(name.StringID + " began play");
	}

	void Observer::Tick(float deltaSeconds) {
		Entity::Tick(deltaSeconds);
	}

	void Observer::Terminate() {

	}

	void Observer::SetupInputComponent(InputComponent* component) {
		component->BindAxis(
			"MoveForward", 
			[this](float axisReading, float deltaTime) {
				MoveForward(axisReading, deltaTime);
			}
		);

		component->BindAxis(
			"MoveRight",
			[this](float axisReading, float deltaTime) {
				MoveRight(axisReading, deltaTime);
			}
		);

		component->BindAxis(
			"LookUp",
			[this](float axisReading, float deltaTime) {
				LookUp(axisReading, deltaTime);
			}
		);

		component->BindAxis(
			"LookRight",
			[this](float axisReading, float deltaTime) {
				LookRight(axisReading, deltaTime);
			}
		);
	}
	
	void Observer::MoveForward(float axisValue, float deltaTime) {
		auto forward = parent->GetForward();
		auto moveSpeed = MovementSpeed * deltaTime;
		
		auto positon = parent->GetPosition();
		positon += forward * axisValue * moveSpeed;

		parent->SetPosition(positon);
	}

	void Observer::MoveRight(float axisValue, float deltaTime) {
		auto forward = parent->GetForward();
		auto right = forward.Cross(parent->GetUp()).Normalize();
		auto moveSpeed = MovementSpeed * deltaTime;

		auto positon = parent->GetPosition();
		positon += right * axisValue * moveSpeed;

		parent->SetPosition(positon);
	}

	void Observer::LookUp(float axisValue, float deltaTime) {
		math::Rotator deltaRotation(axisValue, 0, 0);
		
		//Clamp look radius to avoid quaternion flipping over
		if (axisValue > 89) {
			axisValue = 89;
		}
		else if (axisValue < -89) {
			axisValue = -89;
		}

		auto rotation = parent->GetRotation();
		rotation = rotation * math::Quaternion(deltaRotation);

		parent->SetRotation(rotation);
	}

	void Observer::LookRight(float axisValue, float deltaTime) {
		math::Rotator deltaRotation(0, -axisValue, 0);

		auto rotation = parent->GetRotation();
		rotation = rotation * math::Quaternion(deltaRotation);
		
		parent->SetRotation(rotation);
	}
}