//STD Headers

//Library Headers

//Void Engine Headers
#include "Entity.h"

namespace EngineCore {
	///CTORS
	Entity::Entity() {

	}

	Entity::~Entity() {

	}

	EngineMath::Vector3<float> Entity::GetPostion() {
		return Position;
	}
}
