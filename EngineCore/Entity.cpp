//STD Headers

//Library Headers

//Void Engine Headers
#include "Entity.h"
#include "Component.h"

namespace EngineCore {
	Entity::Entity(const EngineUtils::Name& name) : ID(std::move(name)), Velocity(0.0f) {
	
	}

	Entity::Entity(const std::string& name) : Entity(EngineUtils::Name(name)) {

	}

	Entity::~Entity() {
		for (auto& component : Components) {
			delete component;
		}
	}

	void Entity::Input(const InputEvent& input, float deltaTime){
		for (auto& component : Components) {
			component->Input(input, deltaTime);
		}
	}

	void Entity::Tick(float deltaTime) {
		for (auto& component : Components) {
			component->Tick(deltaTime);
		}
	}

	void Entity::Draw() const {
		for (auto& component : Components) {
			component->Draw();
		}
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

	void Entity::AddComponent(Component* component) {
		Components.push_back(component);
	}
	
}
