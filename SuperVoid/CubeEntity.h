#pragma once
//STD Headers

//Engine Headers
#include "Entity.h"
#include "GraphicsComponent.h"

//SuperVoid Headers

namespace SuperVoid {

	class CubeEntity : public core::Entity {
	public: 
		/**
		 * Constructor
		 */
		CubeEntity(const std::string& name);
		
		/**
		 * Constructor
		 * @param name The entity's name
		 */
		CubeEntity(const utils::Name& name);
		
		/**
		 * Destructor
		 */
		~CubeEntity();

		/**
		 * Function that defines what the entity does once a level begins.
		 * @note This function largely acts like an initialization function
		 */
		void BeginPlay() override;

		/**
		 * Function that defines how an entity processes updates
		 * @param deltaSeconds the time elapsed since the previous tick
		 */
		void Tick(float deltaSeconds) override;

		/**
		 * Defines entity death behaviors
		 */
		void Terminate() override;

	private:
		float Velocity;

	};

}