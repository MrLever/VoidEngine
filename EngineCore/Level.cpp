//STD Headers

//Library Headers

//Coati Headers
#include "Level.h"
#include "ResourceManager.h"
#include "EntityData.h"

namespace core {

	Level::Level(const std::string& levelPath) : Resource(levelPath), LevelName("Error"), LevelEntityFactory(this) {
		ActiveCamera = nullptr;
		EntityDataPool = nullptr;
		GameThreadPool = nullptr;
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

	bool Level::LoadErrorResource() {
		return false;
	}

	void Level::Initialize() {
		if (!GameThreadPool) {
			utils::Logger::LogError("Composite Resource Level does not have access to ThreadPool. \nCannot construct resource manager for child resources");
		}
		else {
			EntityDataPool = std::make_shared<utils::ResourceManager<EntityData>>(GameThreadPool);
		}

		for (auto& entity : LevelData["entities"]) {
			
		}
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
}