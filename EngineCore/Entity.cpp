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
		for (auto& component : Components) {
			delete component;
		}
	}

	void Entity::Input(const KeyboardInput& input){
		for (auto& component : Components) {
			component->Input(input);
		}
	}

	void Entity::Input(const MouseInput& input){
		for (auto& component : Components) {
			component->Input(input);
		}
	}

	void Entity::Input(const GamepadInput& input) {
		for (auto& component : Components) {
			component->Input(input);
		}
	}

	void Entity::Tick(float deltaSeconds) {
		for (auto& component : Components) {
			component->Tick(deltaSeconds);
		}
	}

	void Entity::Draw() const {
		if (GraphicsData == nullptr) {
			return;
		}

		GraphicsData->SetPosition(Position);
		GraphicsData->SetRotation(Rotation);

		GraphicsData->Draw();
	}

	EngineMath::Vector3 Entity::GetPostion() {
		return Position;
	}

	void Entity::SetPosition(const EngineMath::Vector3& newPosition) {
		Position = newPosition;
	}

	EngineMath::Rotator Entity::GetRotation() {
		return Rotation;
	}

	void Entity::SetRotation(const EngineMath::Rotator& newRotation) {
		Rotation = newRotation;
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
