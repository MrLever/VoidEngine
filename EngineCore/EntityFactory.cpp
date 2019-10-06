//STD Headers

//Library Headers

//Void Engine Headers
#include "EntityFactory.h"
#include "CubeEntity.h"
#include "BouncingCube.h"
#include "ComponentFactory.h"
#include "PlayerEntity.h"
#include "Level.h"

namespace core {
	EntityFactory::EntityFactory(Level* currLevel) : CurrLevel(currLevel), CompFactory(currLevel) {

	}

	void EntityFactory::CreateEntityList(const nlohmann::json& entityList) {
		//Preload entity data for entity factory to take advantage of parallel loading
		auto list = CurrLevel->LevelData["entities"];
		for (auto& entity : list) {
			std::string source = "Resources/Entities/" + entity["type"].get<std::string>() + ".json";
			CurrLevel->EntityDataPool->LoadResource(source);
		}

		for (const auto& entityEntry : entityList) {
			std::string source = "Resources/Entities/" + entityEntry["type"].get<std::string>() + ".json";
			auto entityResource = CurrLevel->EntityDataPool->GetResource(source);
			auto entity = CreateEntity(*entityResource);

			if (entity == nullptr) {
				utils::Logger::LogWarning("Entity construction for " + entityEntry["name"].get<std::string>() + " failed");
				continue;
			}

			CurrLevel->Entities.push_back(entity);
		}
	}

	Entity* EntityFactory::CreateEntity(const EntityData& entityData) {
		/*auto entityName = entityData["name"].get<std::string>();
		std::string type = entityData["type"].get<std::string>();*/
		
		Entity* entity = nullptr;

		////Construct the entity on the heap
		//if (type == "PlayerEntity") {
		//	entity = new PlayerEntity(entityName);
		//}
		//else if (type == "CubeEntity") {
		//	entity = new SuperVoid::CubeEntity(entityName);
		//}
		//else if (type == "BouncingCube") {
		//	entity = new SuperVoid::BouncingCube(entityName);
		//}

		//SetWorldOrientation(entityData, entity);

		//if (entityData.find("components") != entityData.end()) {
		//	auto componentData = entityData["components"];
		//	CompFactory.ProcessComponentData(entity, componentData);
		//}

		return entity;
	}

	void EntityFactory::SetWorldOrientation(const nlohmann::json& entityData, core::Entity* entity) {
		//Extract Entity position
		math::Vector3 position;
		position.X = entityData["location"][0].get<float>();
		position.Y = entityData["location"][1].get<float>();
		position.Z = entityData["location"][2].get<float>();

		math::Rotator rotation;
		rotation.Pitch = entityData["rotation"][0].get<float>();
		rotation.Yaw = entityData["rotation"][1].get<float>();
		rotation.Roll = entityData["rotation"][2].get<float>();

		entity->SetPosition(position);
		entity->SetRotation(rotation);
	}

}