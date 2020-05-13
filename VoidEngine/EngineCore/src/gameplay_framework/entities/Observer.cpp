//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/factory/Factory.h"
#include "utils/Logger.h"

#include "gameplay_framework/entities/Observer.h"
#include "rendering/Components/CameraComponent.h"

namespace core {

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

		component->BindAxis(
			"MoveUp",
			[this](float axisReading, float deltaTime) {
				MoveUp(axisReading, deltaTime);
			}
		);
	}
	
	void Observer::MoveForward(float axisValue, float deltaTime) {
		auto forward = GetForward();
		auto moveSpeed = MovementSpeed * deltaTime;
		
		transform.position += (forward * axisValue * moveSpeed);
	}

	void Observer::MoveRight(float axisValue, float deltaTime) {
		auto forward = GetForward();
		auto right = forward.Cross(GetUp()).Normalize();
		auto moveSpeed = MovementSpeed * deltaTime;

		transform.position += right * axisValue * moveSpeed;
	}

	void Observer::MoveUp(float axisValue, float deltaTime) {
		transform.position += math::Vector3::Up * axisValue * deltaTime * MovementSpeed;
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

		//Remove roll introduced by quaternion calculations
		auto rotation = transform.rotation * deltaRotation;
		auto euler = rotation.AsEuler();
		euler.Roll = 0;

		SetLocalRotation(euler.AsQuaternion());
	}

	void Observer::LookRight(float axisValue, float deltaTime) {
		math::Rotator deltaRotation(0, -axisValue, 0);

		SetRotation((GetRotation() * math::Quaternion(deltaRotation)).Normalize());
	}
}