//STD Headers

//Library Headers

//Void Engine Headers
#include "EntityFactory.h"
#include "CubeEntity.h"
#include "ComponentFactory.h"
#include "PlayerEntity.h"
#include "Level.h"

namespace EngineCore {
	EntityFactory::EntityFactory(Level* currLevel) : CurrLevel(currLevel), CompFactory(currLevel) {

	}

	void EntityFactory::CreateEntityList(const nlohmann::json& entityList) {
		for (const auto& entity : entityList) {
			CurrLevel->Entities.push_back(CreateEntity(entity));
		}

	}

	Entity* EntityFactory::CreateEntity(const nlohmann::json& entityData) {
		auto entityName = entityData["name"].get<std::string>();
		std::string type = entityData["type"].get<std::string>();
		//Construct the entity on the heap
		Entity* entity = nullptr;

		if (type == "PlayerEntity") {
			entity = new PlayerEntity(entityName);
		}
		else if (type == "CubeEntity") {
			entity = new SuperVoid::CubeEntity(entityName);
		}

		SetWorldOrientation(entityData, entity);

		if (entityData.find("components") != entityData.end()) {
			auto componentData = entityData["components"];
			CompFactory.ProcessComponentData(entity, componentData);
		}

		return entity;
	}

	void EntityFactory::SetWorldOrientation(const nlohmann::json& entityData, EngineCore::Entity* entity) {
		//Extract Entity position
		EngineMath::Vector3 position;
		position.X = entityData["location"][0].get<float>();
		position.Y = entityData["location"][1].get<float>();
		position.Z = entityData["location"][2].get<float>();

		EngineMath::Rotator rotation;
		rotation.Pitch = entityData["rotation"][0].get<float>();
		rotation.Yaw = entityData["rotation"][1].get<float>();
		rotation.Roll = entityData["rotation"][2].get<float>();

		entity->SetPosition(position);
		entity->SetRotation(rotation);
	}

}