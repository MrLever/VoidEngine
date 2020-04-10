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
	
	Entity::Entity() : name("Entity"), world(nullptr), parent(nullptr) {
	
	}

	Entity::~Entity() {

	}

	void Entity::Input(const InputAction& input, float deltaTime) {
		for (auto& component : components) {
			component->Input(input, deltaTime);
		}
	}

	void Entity::Input(const AxisInputAction& input, float deltaTime) {
		for (auto& component : components) {
			component->Input(input, deltaTime);
		}
	}

	void Entity::Initialize() {
		if (!ConfigData.is_null()) {
			name = utils::Name(ConfigData["name"]);

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
		
		for (auto& component : components) {
			component->Initialize();
		}

		for (auto& child : children) {
			child->Initialize();
		}
	}

	void Entity::BeginPlay() {
		for (auto& child : children) {
			child->BeginPlay();
		}
	}

	void Entity::Tick(float deltaTime) {
		for (auto& component : components) {
			component->Tick(deltaTime);
		}

		for (auto& child : children) {
			child->Tick(deltaTime);
		}
	}

	void Entity::Terminate() {
		;
	}

	void Entity::Draw() const {
		for (auto& component : components) {
			component->Draw();
		}

		for (auto& child : children) {
			child->Draw();
		}
	}

	void Entity::OnHit() {
		;
	}

	void Entity::OnDestroy() {
		;
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
		return name.StringID;
	}

	void Entity::SetName(const std::string& name) {
		this->name = utils::Name(name);
	}

	void Entity::SetName(const utils::Name& name) {
		this->name = name;
	}

	void Entity::AddComponent(std::shared_ptr<Component> component) {
		//Abuse friendship to give the child component necessary references
		component->parent = this;
		component->transform = &transform;

		//Register component
		components.insert(component);
	}

	void Entity::AddComponent(Component* component) {
		std::shared_ptr<Component> wrappedPtr(component);

		AddComponent(wrappedPtr);
	}

	Scene* Entity::GetWorld() const {
		return world;
	}

	void Entity::SetScene(Scene* world) {
		world = world;
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
		children.emplace_back(std::move(child));
	}

	std::unique_ptr<Entity> Entity::RemoveChild(Entity* entity) {
		//Search over children, remove the requested child, and transfer ownership
		for (auto it = children.begin(); it != children.end(); it++) {
			if (it->get() == entity) {
				auto handle = std::move(*it);
				
				children.erase(it);

				return handle;
			}
		}

		return std::unique_ptr<Entity>();
	}

	void Entity::Destroy() {
		GetWorld()->Destroy(this);
	}

	void Entity::DestroyFromChildren(std::unordered_set<Entity*>& destructionList) {
		for (auto it = children.rbegin(); it != children.rend(); it++) {
			auto child = (*it).get();

			if (destructionList.find(child) != destructionList.end()) {
				auto handle = std::move(*it);
				handle->OnDestroy();
				handle.reset();
				continue;
			}

			child->DestroyFromChildren(destructionList);
		}
	}
}
