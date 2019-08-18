#pragma once
//STD Headers
#include <string>

//Library headers
#include "Vector.h"

//Void Engine Headers

namespace EngineCore {

	/**
	 * @class The Entity class defines the basic definition of what it takes to partake in the simulation
	 */
	class Entity {
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
		 * Pure virtual function that defines what the entity does once a level begins.
		 * @note This function largely acts like an initialization function
		 */
		virtual void BeginPlay() = 0;

		/**
		 * Pure virtual function that defines how an entity processes 
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

		EngineMath::Vector3<float> GetPostion();
	
	private:
		EngineMath::Vector3<float> Position;
	};
}