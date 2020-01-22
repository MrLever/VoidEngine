#pragma once
//STD Headers
#include <string>

//Library headers

//Void Engine Headers
#include "FactoryConstructible.h"
#include "EntityData.h"
#include "Name.h"
#include "EngineMath/Vector.h"
#include "EngineMath/Rotator.h"
#include "EngineMath/Quaternion.h"
#include "InputAction.h"
#include "AxisInputAction.h"
#include "Factory.h"

namespace core {
	//Forward class declarations
	class Component;
	class Level;

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
		 * Accessors for entity position
		 */
		math::Vector3 GetPostion();
		void SetPosition(const math::Vector3& newPosition);

		/**
		 * Accessors for entity rotation
		 */
		math::Rotator GetRotation();
		void SetRotation(const math::Rotator& newRotation);

		/**
		 * Acessors for entity name
		 */
		std::string GetName();
		void SetName(const std::string& name);
		void SetName(const utils::Name& name);

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
		Level* GetWorld() const;
		void SetWorld(Level* world);
	
		/**
		 * Accessor for Parent
		 */
		void SetParent(Entity* parent);

	protected:
		/** Entity's name */
		utils::Name ID;

		/** All of the components for this entity */
		std::unordered_map<utils::Name, Component*> Components;

		/** The entity's position in 3D space */
		math::Vector3 Position;

		/** The entity's rotation in 3D space */
		math::Quaternion Rotation;

		/** The level the entity inhabits */
		Level* World;

		/** Optional pointer to the entity's owner */
		Entity* Parent;
	};

	template<class T>
	inline T* Entity::GetComponent() {
		auto componentEntry = Components.find(T::GetStaticTypename());
		if (componentEntry == Components.end()) {
			return nullptr;
		}
		else {
			T* component = reinterpret_cast<T*>(componentEntry->second);
			return component;
		}
	}
}