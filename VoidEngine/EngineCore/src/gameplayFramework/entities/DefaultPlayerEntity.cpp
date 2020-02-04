//STD Headers

//Library Headers

//Void Engine Headers
#include "DefaultPlayerEntity.h"
#include "CameraComponent.h"
#include "utils/factory/Factory.h"
#include "utils/Logger.h"

namespace core {
	TYPE_INFO_IMPL(DefaultPlayerEntity)

	ENABLE_FACTORY(DefaultPlayerEntity, Entity)
	
	
	DefaultPlayerEntity::DefaultPlayerEntity() {

	}

	DefaultPlayerEntity::~DefaultPlayerEntity() {

	}

	void DefaultPlayerEntity::Initialize() {
		PlayerEntity::Initialize();

		MovementSpeed = 10;
	}

	void DefaultPlayerEntity::BeginPlay() {
		utils::Logger::LogInfo(ID.StringID + " began play");
	}

	void DefaultPlayerEntity::Tick(float deltaSeconds) {
		Entity::Tick(deltaSeconds);
	}

	void DefaultPlayerEntity::Terminate() {

	}

	void DefaultPlayerEntity::SetupInputComponent(InputComponent* component) {
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
	
	void DefaultPlayerEntity::MoveForward(float axisValue, float deltaTime) {
		auto forward = Rotation.ToVector();
		auto moveSpeed = MovementSpeed * deltaTime;
		Position += forward * axisValue * moveSpeed;
	}

	void DefaultPlayerEntity::MoveRight(float axisValue, float deltaTime) {
		auto forward = Rotation.ToVector();
		auto right = forward.Cross(math::Vector3(0, 1, 0)).Normalize();
		auto moveSpeed = MovementSpeed * deltaTime;

		Position += right * axisValue * moveSpeed;
	}

	void DefaultPlayerEntity::LookUp(float axisValue, float deltaTime) {
		math::Rotator deltaRotation(0, 0, axisValue);
		Rotation = Rotation * math::Quaternion(deltaRotation);
	}

	void DefaultPlayerEntity::LookRight(float axisValue, float deltaTime) {
		math::Rotator deltaRotation(0, -axisValue, 0);
		Rotation = Rotation * math::Quaternion(deltaRotation);
	}
}