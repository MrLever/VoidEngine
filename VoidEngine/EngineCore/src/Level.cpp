//STD Headers

//Library Headers

//Coati Headers
#include "Level.h"

#include "utils/resource/ResourceAllocator.h"

#include "gameplay_framework/EntityData.h"
#include "gameplay_framework/Component.h"

namespace core {

	Level::Level(const std::string& levelPath) : JsonResource(levelPath), m_Name("Error"){

	}

	Level::~Level() {

	}

	bool Level::LoadErrorResource() {
		return false;
	}

	void Level::Initialize() {
		m_Name = Data["name"].get<std::string>();
	}	

	utils::Name Level::GetName() {
		return m_Name;
	}
}