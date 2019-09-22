//STD Headers

//Library Headers

//Void Engine Headers
#include "Entity.h"

namespace EngineCore {
	///CTORS
	Entity::Entity(const std::string& name) : ID(std::move(name)), GraphicsData(nullptr) {

	}

	Entity::Entity(const EngineUtils::Name& name) : ID(std::move(name)), GraphicsData(nullptr) {
	
	}

	Entity::~Entity() {
		delete GraphicsData;
	}

	void Entity::Draw() const {
		if (GraphicsData == nullptr) {
			return;
		}

		GraphicsData->SetPosition(Position);

		GraphicsData->Draw();
	}

	EngineMath::Vector3 Entity::GetPostion() {
		return Position;
	}

	void Entity::SetPosition(const EngineMath::Vector3& newPosition) {
		Position = newPosition;
	}
	
	void Entity::SetGraphicsComponent(GraphicsComponent* component) {
		if (GraphicsData != nullptr) {
			delete GraphicsData;
			GraphicsData = nullptr;
		}

		GraphicsData = component;
	}

	GraphicsComponent* Entity::GetGraphicsComponent() const {
		return GraphicsData;
	}
}
