#pragma once
//STD Headers

//Engine Headers
#include "Entity.h"
#include "GraphicsComponent.h"

//SuperVoid Headers

namespace SuperVoid {

	class CubeEntity : public EngineCore::Entity {
	public: 
		/**
		 * Constructor
		 */
		CubeEntity(const std::string& name);

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
		void Tick(double deltaSeconds) override;

		/**
		 * Sends draw data for this entity's graphics components to the renderer
		 */
		void Draw() override;

		/**
		 * Defines entity death behaviors
		 */
		void Terminate() override;
	};

}