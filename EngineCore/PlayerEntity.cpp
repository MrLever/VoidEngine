//STD Headers

//Library Headers

//Void Engine Headers
#include "PlayerEntity.h"
#include "Logger.h"

namespace core {
	PlayerEntity::PlayerEntity(const std::string& name) : Entity(name) {

	}

	PlayerEntity::PlayerEntity(const utils::Name& name) : Entity(name) {
	
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