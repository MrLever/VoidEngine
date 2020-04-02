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
		TYPE_INFO_DECL(Entity)

	public:
		/** The entity's transform in 3D space */
		Transform m_Transform;

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
		 * Gets distance between this entity and another
		 */
		float GetDistance(const Entity* const other) const;

		/**
		 * Gets distance between this entity and another
		 */
		float GetDistanceSquared(const Entity* const other) const;

		/**
		 * Accessors for entity position
		 */
		math::Vector3 GetPostion() const;
		void SetPosition(const math::Vector3& newPosition);

		/**
		 * Accessors for entity rotation
		 */
		math::Rotator GetRotation() const;
		void SetRotation(const math::Rotator& newRotation);

		/**
		 * Accessors for entity scale
		 */
		math::Vector3 GetScale() const;
		void SetScale(const math::Vector3& newScale);

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
		 * Returns componet of type T
		 * @tparam T The type of component being requested
		 * @return Component of type T if entity has requested component, else nullptr
		 */
		template<class T>
		T* GetComponent();
	
		/**
		 * Accessors for the pointer to the level this entity is active in
		 */
		Scene* GetWorld() const;
		void SetScene(Scene* world);
	
		/**
		 * Accessor for Parent
		 */
		void SetParent(Entity* parent);

		/**
		 * Accessor for Parent
		 */
		void AddChild(std::shared_ptr<Entity> child);

	protected:
		/** Entity's name */
		utils::Name m_Name;

		/** All of the components for this entity */
		std::unordered_set<std::shared_ptr<Component>> m_Components;

		/** Optional pointer to the entity's owner */
		Entity* m_Parent;
		
		/** List of entity's children */
		std::vector<std::shared_ptr<Entity>> m_Children;

	private:
		/** The level the entity inhabits */
		Scene* m_World;
	};
	
	template<class T>
	inline T* Entity::GetComponent()
	{
		for (auto& component : m_Components) {
			auto ptr = dynamic_cast<T*>(component.get());
			if (ptr != nullptr) {
				return ptr;
			}
		}

		return nullptr;
	}
}