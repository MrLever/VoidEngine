//STD Headers

//Library Headers

//Void Engine Headers
#include "Entity.h"
#include "Component.h"
#include "JsonResource.h"

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

	void Entity::Initialize() {
		if (!ConfigData.is_null()) {
			ID = utils::Name(ConfigData["name"]);

			auto locationData = ConfigData["location"];
			Position.X = locationData[0].get<float>();
			Position.Y = locationData[1].get<float>();
			Position.Z = locationData[2].get<float>();
		
			auto rotationData = ConfigData["rotation"];
			math::Rotator rotation;
			rotation.Roll = rotationData[0].get<float>();
			rotation.Yaw = rotationData[1].get<float>();
			rotation.Pitch = rotationData[2].get<float>();

			Rotation = math::Quaternion(rotation);
		}
		
		for (auto& component : Components) {
			component->Initialize();
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
		return Rotation.ToEuler();
	}

	void Entity::SetRotation(const math::Rotator& newRotation) {
		Rotation = math::Quaternion(newRotation);
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

	void Entity::SetConfigData(const nlohmann::json& data) {
		ConfigData = data;
	}

	void Entity::AddComponent(Component* component) {
		component->SetParent(this);
		Components.push_back(component);
	}
}
