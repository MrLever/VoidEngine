#pragma once
//STD Headers
#include <string>
#include <unordered_set>

//Library headers

//Void Engine Headers
#include "utils/Name.h"
#include "utils/factory/Factory.h"
#include "utils/factory/FactoryConstructible.h"

#include "core/input/InputAction.h"
#include "core/input/AxisInputAction.h"
#include "core/gameplay_framework/EntityData.h"
#include "core/gameplay_framework/Transform.h"

namespace core {
	//Forward class declarations
	class Component;
	class Scene;

	/**
	 * @class Entity 
	 * @brief The Entity class provides the basic definition of what it takes to partake in the simulation
	 */
	class Entity : public utils::FactoryConstructible {
		/**
		 * Declare custom RTTI support
		 */
		ENABLE_RTTI(Entity)

	public:
		/** The entity's LOCAL transform in 3D space */
		Transform transform;

		/**
		 * Constructor
		 */
		Entity();

		/**
		 * Destructor
		 */
		virtual ~Entity();

		/**
		 * Function to allow this component to process input events
		 * @param input Input fromt the keyboard to process
		 */
		virtual void Input(const InputAction& input, float deltaTime);

		/**
		 * Function to allow this component to process input axis data
		 * @param input Input fromt the keyboard to process
		 */
		virtual void Input(const AxisInputAction& input, float deltaTime);

		/**
		 * Allows an entity to configure itself after it is constructed
		 */
		virtual void Initialize();

		/**
		 * Pure virtual function that defines what the entity does once a level begins.
		 * @note This function largely acts like an initialization function
		 */
		virtual void BeginPlay();

		/**
		 * Pure virtual function that defines how an entity processes updates
		 * @param deltaSeconds the time elapsed since the previous tick
		 * @note This function should be called by the derived class tick function
		 */
		virtual void Tick(float deltaTime);

		/**
		 * Defines entity death behaviors
		 */
		virtual void Terminate();

		/**
		 * Command for the renderer to draw the entity
		 */
		virtual void Draw() const;
		
		/**
		 * Allows entity to respond to collision events
		 */
		virtual void OnHit();

		/**
		 * Behaviors for the entity to take on destruction
		 */
		virtual void OnDestroy();

		/**
		 * @return The distance between this entity and another
		 */
		float GetDistance(const Entity* const other) const;

		/**
		 * @return The distance between this entity and another
		 */
		float GetDistanceSquared(const Entity* const other) const;

		/**
		 * @return Entity's position in world space
		 */
		math::Vector3 GetPosition() const;

		/**
		 * Updates local transform to position entity at newPosition in world coordinates
		 */
		void SetPosition(const math::Vector3& newPosition);

		/**
		 * @return the entity's position relative to its parent
		 */
		math::Vector3 GetLocalPosition() const;

		/**
		 * Set the entity's postion relative to its parent
		 */
		void SetLocalPosition(const math::Vector3& newPosition);

		/**
		 * @return the absolute rotation of this entity in world space
		 */
		math::Quaternion GetRotation() const;

		/**
		 * Set the absolute rotation of this entity in world space
		 */
		void SetRotation(const math::Rotator& newRotation);

		/**
		 * Set the absolute rotation of this entity in world space
		 */
		void SetRotation(const math::Quaternion& newRotation);

		/**
		 * @return the Entity's rotation relative to its parent
		 */
		math::Quaternion GetLocalRotation() const;

		/**
		 * Set the entity's rotation relative to its parent
		 */
		void SetLocalRotation(const math::Rotator& newRotation);
		
		/**
		 * Set the entity's rotation relative to its parent
		 */
		void SetLocalRotation(const math::Quaternion& newRotation);
		
		/**
		 * @return The entity's absolute scale
		 */
		math::Vector3 GetScale() const;

		/**
		 * Set the entity's absolute scale
		 */
		void SetScale(const math::Vector3& newScale);

		/**
		 * @return This entity's forward direction in world space
		 */
		math::Vector3 GetForward() const;

		/**
		 * @return This entity's up direction in world space
		 */
		math::Vector3 GetUp() const;

		/**
		 * Acessors for entity name
		 */
		std::string GetName() const;
		void SetName(const std::string& name);
		void SetName(const utils::Name& name);

		/**
		 * Gives ownership of a component to this entity
		 * @param component The component to add
		 */
		void AddComponent(std::shared_ptr<Component> component);

		/**
		 * Gives ownership of a component to this entity
		 * @param component The component to add
		 */
		void AddComponent(Component* component);

		/**
		 * Returns component of type T
		 * @tparam T The type of component being requested
		 * @return Component of type T if entity has requested component, else nullptr
		 */
		template<class T>
		T* GetComponent();
	
		/**
		 * Returns all component of type T attached to this entity
		 * @tparam T The type of component being requested
		 * @return Component of type T if entity has requested component, else nullptr
		 */
		template<class T>
		std::vector<T*> GetComponents();

		/**
		 * Returns first occurent of T in children
		 */
		template <class T>
		T* GetComponentInChildren();

		/**
		 * Returns componet of type T
		 * @tparam T The type of component being requested
		 * @return Component of type T if entity has requested component, else nullptr
		 */
		template<class T>
		std::vector<T*> GetComponentsInChildren();
	
		template<class T>
		void GetComponentsInChildren(std::vector<T*>& components);

		/**
		 * Accessors for the pointer to the level this entity is active in
		 */
		Scene* GetWorld() const;
		void SetScene(Scene* world);
	
		/**
		 * @return Reference this this entity's parent
		 */
		Entity* GetParent() const;

		/**
		 * Accessor for Parent
		 */
		void SetParent(Entity* parent);

		/**
		 * Transfers ownership of an entity to this entity
		 */
		void AddChild(std::unique_ptr<Entity> child);

		/**
		 * Removes ownership of a child from this entity
		 */
		std::unique_ptr<Entity> RemoveChild(Entity* entity);

		/**
		 * Marks this entity for destruction
		 */
		void Destroy();

		/**
		 * Instructs entity to destroy the children in destructionList
		 */
		void DestroyFromChildren(std::unordered_set<Entity*>& destructionList);

		/**
		 * @return the entity's unique identifier
		 */
		unsigned GetID();

	protected:
		/** Entity's name */
		utils::Name name;

		/** All of the components for this entity */
		std::unordered_set<std::shared_ptr<Component>> components;

		/** Optional pointer to the entity's owner */
		Entity* parent;
		
		/** List of entity's children */
		std::vector<std::unique_ptr<Entity>> children;

		std::uint32_t VEID;

	private:
		/** The level the entity inhabits */
		Scene* world;
	};
	
	template<class T>
	inline T* Entity::GetComponent() {
		for (auto& component : components) {
			auto ptr = dynamic_cast<T*>(component.get());
			if (ptr != nullptr) {
				return ptr;
			}
		}

		return nullptr;
	}

	template<class T>
	inline std::vector<T*> Entity::GetComponents() {
		std::vector<T*> foundComponents;

		for (auto& component : components) {
			auto ptr = dynamic_cast<T*>(component.get());
			if (ptr != nullptr) {
				foundComponents.push_back(ptr);
			}
		}

		return foundComponents;
	}

	template<class T>
	inline T* Entity::GetComponentInChildren() {
		auto res = GetComponentsInChildren<T>();
		if (res.size() > 0) {
			return res[0];
		}
		
		return nullptr;
	}
	
	template<class T>
	inline std::vector<T*> Entity::GetComponentsInChildren() {
		std::vector<T*> components;
		for (auto& child : children) {
			auto childComponents = child->GetComponents<T>();
			components.insert(components.end(), childComponents.begin(), childComponents.end());
			child->GetComponentsInChildren<T>(components);
		}
		return components;
	}

	template<class T>
	inline void Entity::GetComponentsInChildren(std::vector<T*>& components) {
		for (auto& child : children) {
			auto childComponents = child->GetComponents<T>();
			components.insert(components.end(), childComponents.begin(), childComponents.end());
			child->GetComponentsInChildren<T>(components);
		}
	}
}