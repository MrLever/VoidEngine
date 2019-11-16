//STD Headers

//Library Headers

//Coati Headers
#include "Level.h"
#include "ResourceAllocator.h"
#include "Component.h"
#include "EntityData.h"

namespace core {

	Level::Level(const std::string& levelPath) : JsonResource(levelPath), LevelName("Error"){
		EntityDataCache = std::make_shared<utils::ResourceAllocator<EntityData>>();
	}

	Level::~Level() {
		for (auto& entity : Entities) {
			delete entity;
			entity = nullptr;
		}
	}

	bool Level::Load() {
		JsonResource::Load();

		auto levelName = Data.find("name");

		if (levelName == Data.end()) {
			return false;
		}

		LevelName = levelName.value();

		return true;
	}

	bool Level::LoadErrorResource() {
		return false;
	}

	void Level::Initialize() {
		utils::Logger::LogInfo("Initializing Level " + LevelName.StringID);
		InputDefinitionPath = JsonResource::GetAttribute<std::string>("controlFile");
		
		//Preload entity data source files for creation
		for (auto& entity : Data["entities"]) {
			std::string source = "Resources/Entities/" + entity["type"].get<std::string>() + ".json";
			EntityDataCache->LoadResource(source);
		}
		
		for (auto& entityWorldData : Data["entities"]) {
			auto entityType = entityWorldData["type"].get<std::string>();
			auto entity = utils::FactoryBase<Entity>::Create(entityType);
			if (entity == nullptr) {
				utils::Logger::LogWarning("Entity type " + entityType + " was not constructed properly. Please register it's factory.");
				continue;
			}

			entity->SetConfigData(entityWorldData);
			entity->Initialize();

			auto entityData = EntityDataCache->GetResource("Resources/Entities/" + entityWorldData["type"].get<std::string>() + ".json");
			auto componentData = entityData->GetAttribute<nlohmann::json>("components");
			if (!componentData.is_null()) {
				for (auto& componentEntry : componentData) {
					auto componentType = componentEntry["type"].get<std::string>();
					auto component = utils::FactoryBase<Component>::Create(componentType);
					if (component) {
						entity->AddComponent(component);
						component->SetComponentData(componentEntry);
						component->Initialize();
					}
				}
			}

			Entities.emplace_back(entity);
		}
	}	

	utils::Name Level::GetName() {
		return LevelName;
	}

	std::string Level::GetControlFilePath() {
		return InputDefinitionPath;
	}

	void Level::BeginPlay() {
		for (auto& entity : Entities) {
			entity->BeginPlay();
		}
	}

	void Level::Update(double deltaTime) {
		for (auto& entity : Entities) {
			entity->Tick(deltaTime);
		}
	}

	std::vector<Entity*> Level::GetScene() {
		return Entities;
	}

}