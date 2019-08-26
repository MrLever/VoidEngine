//STD Headers

//Library Headers

//Void Engine Headers
#include "Entity.h"

namespace EngineCore {
	///CTORS
	Entity::Entity(const std::string& name) : ID(name) {

	}

	Entity::~Entity() {

	}

	EngineMath::Vector3<float> Entity::GetPostion() {
		return Position;
	}
}
