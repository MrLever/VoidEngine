//STD Headers


//Library Headers


//Coati Headers
#include "Level.h"

namespace EngineCore {

	Level::Level(const std::string& levelPath) : Resource(levelPath), LevelName("Error") {

	}

	Level::~Level() {

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

		//auto entities = LevelData.find("entities").value();
		//std::cout << "Entities in level: \n";

		//for (auto& entity : entities) {
		//	std::cout << "Entity: " << entity["name"] << "\n";
		//}

		return true;
	}

	bool Level::LoadErrorResource() {
		return false;
	}

	EngineUtils::Name Level::GetName() {
		return LevelName;
	}

	void Level::Update(double deltaTime) {
		for (auto entity : Entities) {
			entity->Tick(deltaTime);
		}
	}

}