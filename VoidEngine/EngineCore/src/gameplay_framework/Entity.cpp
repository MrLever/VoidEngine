//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/resource/JsonResource.h"

#include "gameplay_framework/Entity.h"
#include "gameplay_framework/Component.h"
#include "Scene.h"

namespace core {

	TYPE_INFO_IMPL(Entity)

	ENABLE_FACTORY(Entity, Entity)
	
	Entity::Entity() : ID("Entity"), m_World(nullptr) {
	
	}

	Entity::~Entity() {
		for (auto& componentEntry : m_Components) {
			delete componentEntry.second;
		}
		m_Components.clear();
	}

	void Entity::Input(const InputAction& input, float deltaTime) {
		for (auto& componentEntry : m_Components) {
			componentEntry.second->Input(input, deltaTime);
		}
	}

	void Entity::Input(const AxisInputAction& input, float deltaTime) {
		for (auto& componentEntry : m_Components) {
			componentEntry.second->Input(input, deltaTime);
		}
	}

	void Entity::Initialize() {
		if (!ConfigData.is_null()) {
			ID = utils::Name(ConfigData["name"]);

			auto locationData = ConfigData["location"];
			m_Position.X = locationData[0].get<float>();
			m_Position.Y = locationData[1].get<float>();
			m_Position.Z = locationData[2].get<float>();
		
			auto rotationData = ConfigData["rotation"];
			m_Rotation = math::Quaternion(
				math::Rotator(
					rotationData[0].get<float>(),
					rotationData[1].get<float>(),
					rotationData[2].get<float>()
				)
			);
		}
		
		for (auto& componentEntry : m_Components) {
			componentEntry.second->Initialize();
		}
	}

	void Entity::BeginPlay() {
		;
	}

	void Entity::Tick(float deltaTime) {
		for (auto& componentEntry : m_Components) {
			componentEntry.second->Tick(deltaTime);
		}
	}

	void Entity::Terminate() {
		;
	}

	void Entity::Draw() const {
		for (auto& componentEntry : m_Components) {
			componentEntry.second->Draw();
		}
	}

	math::Vector3 Entity::GetPostion() {
		return m_Position;
	}

	void Entity::SetPosition(const math::Vector3& newPosition) {
		m_Position = newPosition;
		for (auto& componentEntry : m_Components) {
			componentEntry.second->SetPosition(m_Position);
		}
	}

	math::Rotator Entity::GetRotation() {
		return m_Rotation.ToEuler();
	}

	void Entity::SetRotation(const math::Rotator& newRotation) {
		m_Rotation = math::Quaternion(newRotation);
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
		component->SetParent(this);
		
		auto name = component->GetTypename();
		m_Components[name] = component;
	}

	Scene* Entity::GetWorld() const {
		return m_World;
	}

	void Entity::SetScene(Scene* world) {
		m_World = world;
	}

	void Entity::SetParent(Entity* parent) {
		Parent = parent;
	}

}
