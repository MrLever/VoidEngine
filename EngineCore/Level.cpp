//STD Headers

//Library Headers

//Coati Headers
#include "Level.h"
#include "ResourceAllocator.h"
#include "EntityData.h"

namespace core {

	Level::Level(const std::string& levelPath) : Resource(levelPath), LevelName("Error"){
		EntityDataCache = nullptr;
		GameThreadPool = nullptr;
		IsComposite = true;
	}

	Level::~Level() {
		for (auto& entity : Entities) {
			delete entity;
			entity = nullptr;
		}

		delete LevelEntityFactory;
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
		utils::Logger::LogInfo("Initializing Level " + LevelName.StringID);

		if (!GameThreadPool) {
			utils::Logger::LogError("Composite Resource Level does not have access to ThreadPool");
			utils::Logger::LogError("Level cannot construct resource manager for child resources. Initialization cancelled");
			return;
		}
		

		EntityDataCache = std::make_shared<utils::ResourceAllocator<EntityData>>(GameThreadPool);
		TextureCache = std::make_shared<utils::ResourceAllocator<Texture>>(GameThreadPool);

		LevelEntityFactory = new EntityFactory(this);

		//Preload entity data source files for creation
		for (auto& entity : LevelData["entities"]) {
			std::string source = "Resources/Entities/" + entity["type"].get<std::string>() + ".json";
			EntityDataCache->LoadResource(source);
		}
		
		//Parse entity data source files and spawn actors
		LevelEntityFactory->CreateEntities(LevelData["entities"]);
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

}