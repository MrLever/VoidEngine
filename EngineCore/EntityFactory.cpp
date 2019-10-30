//STD Headers

//Library Headers

//Void Engine Headers
#include "EntityFactory.h"
#include "ComponentFactory.h"
#include "Level.h"

//Entity Includes
#include "DefaultPlayerEntity.h"
#include "PlayerShip.h"
#include "CubeEntity.h"
#include "BouncingCube.h"
#include "StaticObserver.h"

namespace core {
	EntityFactory::EntityFactory(Level* currLevel) : CurrLevel(currLevel), CompFactory(currLevel->ModelCache) {

	}

	void EntityFactory::CreateEntities(const nlohmann::json& entityList) {
		//Preload entity data for entity factory to take advantage of parallel loading
		auto list = CurrLevel->Data["entities"];
		for (const auto& entityEntry : entityList) {

			//Extract data necessary to construct an entity
			utils::Name entityName(entityEntry["name"].get<std::string>());
			std::string entityType = entityEntry["type"].get<std::string>();

			//Get resouce file for the entity type you'll be spawning
			std::string source = "Resources/Entities/" + entityType + ".json";
			auto entityResource = CurrLevel->EntityDataCache->GetResource(source);
			
			//Construct an entity on the heap
			auto entity = CreateEntity(entityName, entityType, *entityResource);

			if (entity == nullptr) {
				utils::Logger::LogError("Entity construction for " + entityEntry["name"].get<std::string>() + " failed");
				continue;
			}

			//Place entity in the world appropriately
			SetWorldOrientation(entityEntry, entity);

			//Return handle to entity on the heap
			CurrLevel->Entities.push_back(entity);
		}
	}

	Entity* EntityFactory::CreateEntity(const utils::Name& name, const std::string& type, const EntityData& data) {
		Entity* entity = nullptr;

		//Construct the entity on the heap
		if (type == "DefaultPlayerEntity") {
			entity = new DefaultPlayerEntity(name);
		}
		else if (type == "CubeEntity") {
			entity = new SuperVoid::CubeEntity(name);
		}
		else if (type == "BouncingCube") {
			entity = new SuperVoid::BouncingCube(name);
		}
		else if (type == "StaticObserver") {
			entity = new StaticObserver(name);
		}
		else if (type == "PlayerShip") {
			entity = new SuperVoid::PlayerShip(name);
		}
		else {
			utils::Logger::LogError("EntityFactory received unkown entity type [" + type + "] Please add it to the know list of entities");
			return entity;
		}

		//After the entity has been constructed, it needs it's components to be attatched
		auto componentData = data.GetAttribute<nlohmann::json>("components");

		if (!componentData.is_null()) {
			CompFactory.ProcessComponentData(entity, componentData);
		}

		entity->Initialize();

		return entity;
	}

	void EntityFactory::SetWorldOrientation(const nlohmann::json& levelData, core::Entity* entity) {
		//Extract Entity position
		math::Vector3 position;
		auto location = levelData["location"];
		position.X = location[0].get<float>();
		position.Y = location[1].get<float>();
		position.Z = location[2].get<float>();

		math::Rotator rotation;
		auto rotationData = levelData["rotation"];
		rotation.Pitch = rotationData[0].get<float>();
		rotation.Yaw = rotationData[1].get<float>();
		rotation.Roll = rotationData[2].get<float>();

		entity->SetPosition(position);
		entity->SetRotation(rotation);
	}

}