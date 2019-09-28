//STD Headers

//Library Headers

//Void Engine Headers
#include "EntityFactory.h"
#include "CubeEntity.h"
#include "PlayerEntity.h"
#include "Level.h"

namespace EngineCore {
	EntityFactory::EntityFactory(Level* currLevel) : CurrLevel(currLevel) {

	}

	void EntityFactory::CreateEntityList(const nlohmann::json& entityList) {
		for (const auto& entity : entityList) {
			std::string type = entity["type"].get<std::string>();

			if (type == "CubeEntity") {
				CurrLevel->Entities.push_back(CreateEntity<SuperVoid::CubeEntity>(entity));
			}
			if (type == "PlayerEntity") {
				CurrLevel->Entities.push_back(CreateEntity<EngineCore::PlayerEntity>(entity));
			}
		}

	}

}