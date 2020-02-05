//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Logger.h"

#include "gameplay_framework/entities/PlayerEntity.h"
#include "rendering/components/CameraComponent.h"

namespace core {

	TYPE_INFO_IMPL(PlayerEntity)

	PlayerEntity::PlayerEntity() : MovementSpeed(0) {
		AddComponent(new InputComponent());
		AddComponent(new CameraComponent());
	}

	void PlayerEntity::Initialize() {
		Entity::Initialize();
		SetupInputComponent(GetComponent<InputComponent>());
	}

	void PlayerEntity::BeginPlay() {
		utils::Logger::LogInfo(ID.StringID + " began play");
	}

	void PlayerEntity::Tick(float deltaSeconds) {
		Entity::Tick(deltaSeconds);
	}

	void PlayerEntity::Terminate() {

	}
}