//STD Headers

//Library Headers

//Void Engine Headers
#include "EntityData.h"


namespace core{

	EntityData::EntityData(const std::string& filepath) : utils::Resource(filepath){

	}

	bool EntityData::Load() {
		return false;
	}
	
	bool EntityData::LoadErrorResource() {
		return false;
	}

	void EntityData::Initialize() {
		;
	}


}
