//STD Headers

//Library Headers

//Void Engine Headers
#include "PlayerEntity.h"
#include "Logger.h"

namespace core {
	PlayerEntity::PlayerEntity() : MovementSpeed(0) {

	}

	void PlayerEntity::Initialize() {
		Entity::Initialize();
		auto inputComponent = new InputComponent();
		Components.insert({InputComponent::GetStaticTypename(), inputComponent });
		SetupInputComponent(inputComponent);
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