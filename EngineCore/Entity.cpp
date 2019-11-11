//STD Headers

//Library Headers

//Void Engine Headers
#include "Entity.h"
#include "Component.h"
#include "JsonResource.h"

namespace core {
	Entity::Entity() : ID("Entity"), PhysicsEnabled(true) {
	
	}

	Entity::~Entity() {
		for (auto& componentEntry : Components) {
			delete componentEntry.second;
		}
		Components.clear();
	}

	void Entity::Input(const InputAction& input, float deltaTime) {
		for (auto& componentEntry : Components) {
			componentEntry.second->Input(input, deltaTime);
		}
	}

	void Entity::Input(const AxisInputAction& input, float deltaTime) {
		for (auto& componentEntry : Components) {
			componentEntry.second->Input(input, deltaTime);
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
			Rotation = math::Quaternion(
				math::Rotator(
					rotationData[0].get<float>(),
					rotationData[1].get<float>(),
					rotationData[2].get<float>()
				)
			);
		}
		
		for (auto& componentEntry : Components) {
			componentEntry.second->Initialize();
		}
	}

	void Entity::Tick(float deltaTime) {
		for (auto& componentEntry : Components) {
			componentEntry.second->Tick(deltaTime);
		}
	}

	void Entity::Draw() const {
		for (auto& componentEntry : Components) {
			componentEntry.second->Draw();
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
		auto name = component->GetTypename();

		Components.insert({ name, component });
	}
}
