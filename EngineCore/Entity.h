#pragma once
//STD Headers
#include <string>

//Library headers

//Void Engine Headers
#include "EntityData.h"
#include "Name.h"
#include "Vector.h"
#include "Rotator.h"
#include "InputAction.h"
#include "AxisInputAction.h"
#include "Factory.h"

namespace core {
	//Forward class declarations
	class Component;

	/**
	 * @class Entity 
	 * @brief The Entity class provides the basic definition of what it takes to partake in the simulation
	 */
	class Entity {
	public:
		/**
		 * Constructor
		 * @param data The entity's initialization data
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
		virtual void BeginPlay() = 0;

		/**
		 * Pure virtual function that defines how an entity processes updates
		 * @param deltaSeconds the time elapsed since the previous tick
		 * @note This function should be called by the derived class tick function
		 */
		virtual void Tick(float deltaTime);

		/**
		 * Defines entity death behaviors
		 */
		virtual void Terminate() = 0;

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
		 * 
		 */
		void SetConfigData(const nlohmann::json& data);

		/**
		 * Gives ownership of a component to this entity
		 * @param component The component to add
		 */
		void AddComponent(Component* component);
	
	protected:
		/** The entity's position in 3D space */
		math::Vector3 Position;

		/** The entity's rotation in 3D space */
		math::Rotator Rotation;
		
		/** The entity's velocity */
		float Velocity;

		/** Entity's name */
		utils::Name ID;

		nlohmann::json ConfigData;

		/** All of the components for this entity */
		std::vector<Component*> Components;
	};
}