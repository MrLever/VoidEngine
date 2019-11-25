//STD Headers

//Library Headers

//Void Engine Headers
#include "PlayerEntity.h"
#include "Logger.h"

namespace core {
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