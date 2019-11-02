//STD Headers

//Library Headers

//Void Engine Headers
#include "Entity.h"
#include "Component.h"

namespace core {
	Entity::Entity() : ID("Entity"), Velocity(0.0f) {
	
	}

	Entity::~Entity() {
		for (auto& component : Components) {
			delete component;
		}
	}

	void Entity::Input(const InputAction& input, float deltaTime) {
		for (auto& component : Components) {
			component->Input(input, deltaTime);
		}
	}

	void Entity::Input(const AxisInputAction& input, float deltaTime) {
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

	math::Vector3 Entity::GetPostion() {
		return Position;
	}

	void Entity::SetPosition(const math::Vector3& newPosition) {
		Position = newPosition;
	}

	math::Rotator Entity::GetRotation() {
		return Rotation;
	}

	void Entity::SetRotation(const math::Rotator& newRotation) {
		Rotation = newRotation;
	}

	std::string Entity::GetName() {
		return ID.StringID;
	}

	void Entity::SetName(const std::string& name) {
		ID = utils::Name(name);
	}

	void Entity::SetName(const utils::Name& name) {
		ID = name;
	}

	void Entity::AddComponent(Component* component) {
		Components.push_back(component);
	}
	
}
