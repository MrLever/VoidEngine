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
		SetupInputComponent(new InputComponent());
	}

	void PlayerEntity::BeginPlay() {
		utils::Logger::LogInfo(ID.StringID + " began play");
	}

	void PlayerEntity::Tick(float deltaSeconds) {
		Entity::Tick(deltaSeconds);
	}

	void PlayerEntity::Terminate() {

	}

	void PlayerEntity::SetupInputComponent(InputComponent* component) {
		Components.push_back(component);
		component->SetParent(this);
	}
}