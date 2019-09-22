//STD Headers


//Library Headers


//Coati Headers
#include "Level.h"

namespace EngineCore {

	Level::Level(const std::string& levelPath) : Resource(levelPath), LevelName("Error") {

	}

	Level::~Level() {
		for (auto& entity : Entities) {
			delete entity;
			entity = nullptr;
		}
	}

	bool Level::Load() {
		bool dataLoaded = LoadLevelData();

		if (!dataLoaded) {
			return false;
		}

		return true;
	}

	void Level::SpawnEntities() {
		auto entityData = LevelData["entities"];
		Entities = LevelEntityFactory.CreateEntityList(entityData);
	}

	bool Level::LoadErrorResource() {
		return false;
	}

	EngineUtils::Name Level::GetName() {
		return LevelName;
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

	bool Level::LoadLevelData() {
		std::ifstream level(ResourcePath);

		if (!level.is_open()) {
			return LoadErrorResource();
		}

		level >> LevelData;

		auto levelName = LevelData.find("name");

		if (levelName == LevelData.end()) {
			return false;
		}

		LevelName = levelName.value();

		return true;
	}

}