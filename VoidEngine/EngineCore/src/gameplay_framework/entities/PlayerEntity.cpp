//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Logger.h"

#include "gameplay_framework/entities/PlayerEntity.h"

namespace core {

	TYPE_INFO_IMPL(PlayerEntity)

	PlayerEntity::PlayerEntity() : MovementSpeed(0) {
		auto inputComponent = new InputComponent();
		Components.insert({ InputComponent::GetStaticTypename(), inputComponent });
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