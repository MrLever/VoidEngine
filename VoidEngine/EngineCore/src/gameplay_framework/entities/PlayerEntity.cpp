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
	}

	void PlayerEntity::Initialize() {
		Entity::Initialize();
		SetupInputComponent(GetComponent<InputComponent>());
	}

	void PlayerEntity::BeginPlay() {
		utils::Logger::LogInfo(m_Name.StringID + " began play");
	}

	void PlayerEntity::Tick(float deltaSeconds) {
		Entity::Tick(deltaSeconds);
	}

	void PlayerEntity::Terminate() {

	}
}