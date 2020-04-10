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
	
	Entity::Entity() : m_Name("Entity"), m_World(nullptr), parent(nullptr) {
	
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
				transform.position = 
					math::Vector3(locationData[0].get<float>(),
						locationData[1].get<float>(),
						locationData[2].get<float>()
					);
			}

			auto rotationData = ConfigData["rotation"];
			if (!rotationData.is_null()) {
				transform.rotation =
					math::Quaternion(
						math::Rotator(
							rotationData[0].get<float>(),
							rotationData[1].get<float>(),
							rotationData[2].get<float>()
						)
					);
			}

			auto scaleData = ConfigData["scale"];
			if (!scaleData.is_null()) {
				transform.scale =
					math::Vector3(
						scaleData[0].get<float>(),
						scaleData[1].get<float>(),
						scaleData[2].get<float>()
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
		return (GetPosition() - other->GetPosition()).Magnitude();
	}

	float Entity::GetDistanceSquared(const Entity* const other) const {
		return (GetPosition() - other->GetPosition()).MagnitudeSqr();
	}

	math::Vector3 Entity::GetPosition() const {
		if (parent == nullptr) {
			return transform.position;
		}
		else {
			auto parentPos = parent->GetPosition();
			auto parentRotation = parent->GetRotation();
			auto positionInParentSpace = parentRotation.Rotate(transform.position);
			return parentPos + positionInParentSpace;
		}
	}

	void Entity::SetPosition(const math::Vector3& newPosition) {
		if (parent == nullptr) {
			transform.position = newPosition;
		}
		else {
			transform.position = newPosition - parent->GetPosition();
		}
	}

	math::Vector3 Entity::GetLocalPosition() const {
		return transform.position;
	}

	void Entity::SetLocalPosition(const math::Vector3& newPosition) {
		transform.position = newPosition;
	}

	math::Quaternion Entity::GetRotation() const {
		return (parent == nullptr) ?
			transform.rotation :
			parent->GetRotation() * transform.rotation;
	}

	void Entity::SetRotation(const math::Rotator& newRotation) {
		SetRotation(math::Quaternion(newRotation));
	}

	void Entity::SetRotation(const math::Quaternion& newRotation) {
		if (parent == nullptr) {
			transform.rotation = newRotation;
		}
		else {
			transform.rotation = newRotation * parent->GetRotation().Inverse();
		}
	}

	math::Quaternion Entity::GetLocalRotation() const {
		return transform.rotation;
	}

	void Entity::SetLocalRotation(const math::Rotator& newRotation) {
		SetLocalRotation(math::Quaternion(newRotation));
	}

	void Entity::SetLocalRotation(const math::Quaternion& newRotation) {
		transform.rotation = newRotation;
	}

	math::Vector3 Entity::GetScale() const {
		return transform.scale;
	}

	void Entity::SetScale(const math::Vector3& newScale) {
		transform.scale = newScale;
	}

	math::Vector3 Entity::GetForward() const {
		return GetRotation().Normalize().Rotate(math::Vector3::Forward);
	}

	math::Vector3 Entity::GetUp() const {
		return  GetRotation().Normalize().Rotate(math::Vector3::Up);
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
		component->parent = this;
		component->transform = &transform;

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
		return parent;
	}

	void Entity::SetParent(Entity* parent) {
		if (parent == nullptr) {
			//Scene is the holder of the entity's unique pointer. Go get it.
			GetWorld()->Reparent(this, parent);
		}
		else {
			//Get the unique handle from the old parent entity, 
			//and give it to the new one. 
			parent->AddChild(parent->RemoveChild(this));
		}

	}

	void Entity::AddChild(std::unique_ptr<Entity> child) {
		child->parent = this;
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
