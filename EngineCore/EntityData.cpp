//STD Headers

//Library Headers

//Void Engine Headers
#include "EntityData.h"


namespace core{

	EntityData::EntityData(const std::string& filepath) : utils::Resource(filepath){

	}

	bool EntityData::Load() {
		std::ifstream entityDefinition(ResourcePath);

		if (!entityDefinition.is_open()) {
			return LoadErrorResource();
		}

		entityDefinition >> Data;
		return true;
	}
	
	bool EntityData::LoadErrorResource() {
		return false;
	}

	void EntityData::Initialize() {
		;
	}


}
