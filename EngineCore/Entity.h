#pragma once
//STD Headers
#include <string>

//Library headers

//Void Engine Headers
#include "Name.h"
#include "GraphicsComponent.h"
#include "Vector.h"

namespace EngineCore {

	/**
	 * @class The Entity class defines the basic definition of what it takes to partake in the simulation
	 */
	class Entity {
	public:
		/**
		 * Constructor
		 * @param name The entity's name
		 */
		Entity(const std::string& name);

		/**
		 * Constructor
		 * @param name The entity's name
		 */
		Entity(const EngineUtils::Name& name);

		/**
		 * Destructor
		 */
		virtual ~Entity();

		/**
		 * Pure virtual function that defines what the entity does once a level begins.
		 * @note This function largely acts like an initialization function
		 */
		virtual void BeginPlay() = 0;

		/**
		 * Pure virtual function that defines how an entity processes updates
		 * @param deltaSeconds the time elapsed since the previous tick
		 */
		virtual void Tick(double deltaSeconds) = 0;

		/**
		 * Sends draw data for this entity's graphics components to the renderer
		 */
		virtual void Draw() = 0;

		/**
		 * Defines entity death behaviors
		 */
		virtual void Terminate() = 0;
		
		/**
		 * Function to request position of this entity
		 * @return The entity's position
		 */
		EngineMath::Vector3<float> GetPostion();

		/**
		 * Function to set Grahpics Component
		 */
		void SetGraphicsComponent(GraphicsComponent* component);

		/**
		 * Function to get a pointer to this entity's graphics data
		 * @return this enity's graphics component
		 */
		GraphicsComponent* GetGraphicsComponent();
	
	protected:
		/** The entity's position in 3D space */
		EngineMath::Vector3<float> Position;

		/** The entity's rotation (pitch, roll, yaw) */
		//EngineMath::Rotator<float> Rotation;
		
		/** Entity's name */
		EngineUtils::Name ID;


		GraphicsComponent* GraphicsData;
	};
}