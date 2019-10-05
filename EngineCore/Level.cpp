//STD Headers

//Library Headers

//Coati Headers
#include "Level.h"
#include "ResourceManager.h"
#include "EntityData.h"

namespace core {

	Level::Level(const std::string& levelPath) : Resource(levelPath), LevelName("Error"), LevelEntityFactory(this) {
		ActiveCamera = nullptr;

		//Inform the resource manager that this resource requires other resources to be loaded 
		IsComposite = true;
	}

	Level::~Level() {
		for (auto& entity : Entities) {
			delete entity;
			entity = nullptr;
		}
	}

	bool Level::Load() {
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

	void Level::LoadComposite(utils::ResourceManager* manager) {
		for (auto& entity : LevelData["entities"]) {
			manager->LoadResource<EntityData>("Resources/Entities/" + entity["type"].get<std::string>() + ".json");
		}
	}

	bool Level::LoadErrorResource() {
		return false;
	}

	void Level::Initialize() {

	}	

	utils::Name Level::GetName() {
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

	CameraComponent* Level::GetActiveCamera() {
		return ActiveCamera;
	}

	bool Level::LoadLevelData() {

	}

}