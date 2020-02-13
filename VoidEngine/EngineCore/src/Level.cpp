//STD Headers

//Library Headers

//Coati Headers
#include "Level.h"

#include "utils/resource/ResourceAllocator.h"

#include "gameplay_framework/EntityData.h"
#include "gameplay_framework/Component.h"

namespace core {

	Level::Level(const std::string& levelPath) : JsonResource(levelPath), LevelName("Error"){

	}

	Level::~Level() {

	}

	bool Level::LoadErrorResource() {
		return false;
	}

	void Level::Initialize() {
		LevelName = Data["name"];
	}	

	utils::Name Level::GetName() {
		return LevelName;
	}
}