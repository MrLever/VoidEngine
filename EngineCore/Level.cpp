//STD Headers


//Library Headers


//Coati Headers
#include "Level.h"

namespace EngineCore {

	Level::Level(const std::string& filepath) : Resource(filepath) {

	}


	Level::~Level() {

	}

	bool Level::Load() {
		std::ifstream level(ResourcePath);

		if (!level.is_open()) {
			return LoadErrorResource();
		}

		level >> LevelData;

		std::cout << LevelData;
		return true;
	}

	bool Level::LoadErrorResource() {
		return false;
	}

}