//STD Headers

//Library Headers

//Coati Headers
#include "Level.h"

#include "utils/resource/ResourceAllocator.h"

#include "gameplay_framework/EntityData.h"
#include "gameplay_framework/Component.h"

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
		auto entityList = Data["entities"];
		
		for (auto& entityData : entityList) {
			auto entityType = entityData["type"].get<std::string>();
			auto entity = utils::FactoryBase<Entity>::Create(entityType);
			if (entity == nullptr) {
				utils::Logger::LogWarning("Entity type " + entityType + " was not constructed properly. Please register its factory.");
				continue;
			}

			entity->SetConfigData(entityData);
			entity->SetWorld(this);

			nlohmann::json componentList;
			if (entityData.find("components") != entityData.end()) {
				componentList = entityData["components"];
			}

			for (auto componentEntry : componentList) {
				auto componentType = componentEntry["type"].get<std::string>();
				auto component = utils::FactoryBase<Component>::Create(componentType);
				if (component) {
					entity->AddComponent(component);
					component->SetConfigData(componentEntry);
				}
			}

			entity->Initialize();
			Entities.emplace_back(entity);
		}
	}	

	void Level::BeginPlay() {
		for (auto& entity : Entities) {
			entity->BeginPlay();
		}
	}

	void Level::Update(float deltaTime) {
		for (auto& entity : Entities) {
			entity->Tick(deltaTime);
		}
	}

	Entity* Level::SpawnEntity(const utils::Name& type, Entity* parent) {
		auto entity = utils::FactoryBase<Entity>::Create(type);
		if (!entity) {
			return nullptr;
		}

		Entities.push_back(entity);
		entity->SetWorld(this);
		entity->SetParent(parent);
		entity->Initialize();
		entity->BeginPlay();
		return entity;
	}

	void Level::DestroyEntity(Entity* entity) {
		;
	}

	std::vector<Entity*> Level::GetScene() {
		return Entities;
	}

	utils::Name Level::GetName() {
		return LevelName;
	}

	std::string Level::GetControlFilePath() {
		return InputDefinitionPath;
	}
}