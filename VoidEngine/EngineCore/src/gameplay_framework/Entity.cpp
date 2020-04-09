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
	
	Entity::Entity() : m_Name("Entity"), m_World(nullptr), m_Parent(nullptr), m_Transform(*this) {
	
	}

	Entity::~Entity() {

	}

	void Entity::Input(const InputAction& input, float deltaTime) {
		for (auto& component : m_Components) {
			component->Input(input, deltaTime);
		}
	}

	void Entity::Input(const AxisInputAction& input, float deltaTime) {
		for (auto& component : m_Components) {
			component->Input(input, deltaTime);
		}
	}

	void Entity::Initialize() {
		if (!ConfigData.is_null()) {
			m_Name = utils::Name(ConfigData["name"]);

			auto locationData = ConfigData["location"];
			if (!locationData.is_null()) {
				m_Transform.SetLocalPosition(
					math::Vector3(
						locationData[0].get<float>(),
						locationData[1].get<float>(),
						locationData[2].get<float>()
					)
				);
			}

			auto rotationData = ConfigData["rotation"];
			if (!rotationData.is_null()) {
				m_Transform.SetLocalRotation(
					math::Quaternion(
						math::Rotator(
							rotationData[0].get<float>(),
							rotationData[1].get<float>(),
							rotationData[2].get<float>()
						)
					)
				);
			}

			auto scaleData = ConfigData["scale"];
			if (!scaleData.is_null()) {
				m_Transform.SetLocalScale(
					math::Vector3(
						scaleData[0].get<float>(),
						scaleData[1].get<float>(),
						scaleData[2].get<float>()
					)
				);
			}
		}
		
		for (auto& component : m_Components) {
			component->Initialize();
		}

		for (auto& child : m_Children) {
			child->Initialize();
		}
	}

	void Entity::BeginPlay() {
		for (auto& child : m_Children) {
			child->BeginPlay();
		}
	}

	void Entity::Tick(float deltaTime) {
		for (auto& component : m_Components) {
			component->Tick(deltaTime);
		}

		for (auto& child : m_Children) {
			child->Tick(deltaTime);
		}
	}

	void Entity::Terminate() {
		;
	}

	void Entity::Draw() const {
		for (auto& component : m_Components) {
			component->Draw();
		}

		for (auto& child : m_Children) {
			child->Draw();
		}
	}

	float Entity::GetDistance(const Entity* const other) const {
		return (m_Transform.GetPosition() - other->GetPosition()).Magnitude();
	}

	float Entity::GetDistanceSquared(const Entity* const other) const {
		return (m_Transform.GetPosition() - other->GetPosition()).MagnitudeSqr();
	}

	math::Vector3 Entity::GetPosition() const {
		return m_Transform.GetPosition();
	}

	void Entity::SetPosition(const math::Vector3& newPosition) {
		m_Transform.SetPosition(newPosition);
	}

	math::Vector3 Entity::GetLocalPosition() const {
		return m_Transform.GetLocalPosition();
	}

	void Entity::SetLocalPosition(const math::Vector3& newPosition) {
		m_Transform.SetLocalPosition(newPosition);
	}

	math::Rotator Entity::GetRotation() const {
		return m_Transform.GetRotation().ToEuler();
	}

	void Entity::SetRotation(const math::Rotator& newRotation) {
		m_Transform.SetRotation(math::Quaternion(newRotation));
	}

	math::Vector3 Entity::GetScale() const {
		return m_Transform.GetScale();
	}

	void Entity::SetScale(const math::Vector3& newScale) {
		m_Transform.SetScale(newScale);
	}

	std::string Entity::GetName() const {
		return m_Name.StringID;
	}

	void Entity::SetName(const std::string& name) {
		m_Name = utils::Name(name);
	}

	void Entity::SetName(const utils::Name& name) {
		m_Name = name;
	}

	void Entity::AddComponent(std::shared_ptr<Component> component) {
		//Abuse friendship to give the child component necessary references
		component->m_Parent = this;
		component->m_Transform = &m_Transform;

		//Register component
		m_Components.insert(component);
	}

	void Entity::AddComponent(Component* component) {
		std::shared_ptr<Component> wrappedPtr(component);

		AddComponent(wrappedPtr);
	}

	Scene* Entity::GetWorld() const {
		return m_World;
	}

	void Entity::SetScene(Scene* world) {
		m_World = world;
	}

	Entity* Entity::GetParent() const {
		return m_Parent;
	}

	void Entity::SetParent(Entity* parent) {
		if (m_Parent == nullptr) {
			//Scene is the holder of the entity's unique pointer. Go get it.
			GetWorld()->Reparent(this, parent);
		}
		else {
			//Get the unique handle from the old parent entity, 
			//and give it to the new one. 
			parent->AddChild(m_Parent->RemoveChild(this));
		}

	}

	void Entity::AddChild(std::unique_ptr<Entity> child) {
		child->m_Parent = this;
		m_Children.emplace_back(std::move(child));
	}

	std::unique_ptr<Entity> Entity::RemoveChild(Entity* child) {
		for (auto it = m_Children.begin(); it != m_Children.end(); it++) {
			if (child = it->get()) {
				auto uniqueHandle = std::move((*it));
				m_Children.erase(it);
				return uniqueHandle;
			}
		}

		return std::unique_ptr<Entity>();
	}

}
