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
		utils::Logger::LogInfo(ID.StringID + " began play");
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
		auto forward = Rotation.ToVector();
		auto moveSpeed = MovementSpeed * deltaTime;
		Position += forward * axisValue * moveSpeed;
	}

	void Observer::MoveRight(float axisValue, float deltaTime) {
		auto forward = Rotation.ToVector();
		auto right = forward.Cross(math::Vector3(0, 1, 0)).Normalize();
		auto moveSpeed = MovementSpeed * deltaTime;

		Position += right * axisValue * moveSpeed;
	}

	void Observer::LookUp(float axisValue, float deltaTime) {
		math::Rotator deltaRotation(0, 0, axisValue);
		Rotation = Rotation * math::Quaternion(deltaRotation);
	}

	void Observer::LookRight(float axisValue, float deltaTime) {
		math::Rotator deltaRotation(0, -axisValue, 0);
		Rotation = Rotation * math::Quaternion(deltaRotation);
	}
}