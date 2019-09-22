#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Entity.h"
#include "Name.h"

namespace EngineCore {
	
	/**
	 * @class PlayerEntity
	 * @brief Specialized Entity designed to be controlled directly by the player
	 */
	class PlayerEntity : public Entity {
	public:
		/**
		 * Defines what the entity does once a level begins.
		 */
		virtual void BeginPlay() override;

		/**
		 * Function that defines how an entity processes updates
		 * @param deltaSeconds the time elapsed since the previous tick
		 */
		virtual void Tick(float deltaSeconds) override;

		/**
		 * Defines entity death behaviors
		 */
		virtual void Terminate() override;
	};

}

