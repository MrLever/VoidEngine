//STD Headers

//Library Headers

//Void Engine Headers
#include "Entity.h"

namespace EngineCore {
	///CTORS
	Entity::Entity(const std::string& name) : ID(std::move(name)) {

	}

	Entity::Entity(const EngineUtils::Name& name) : ID(std::move(name)) {
	}

	Entity::~Entity() {

	}

	GraphicsComponent Entity::Draw() {
		return GraphicsComponent();
	}

	EngineMath::Vector3<float> Entity::GetPostion() {
		return Position;
	}
}
