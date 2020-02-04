#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Name.h"

#include "Entity.h"
#include "InputComponent.h"

namespace core {
	
	/**
	 * @class PlayerEntity
	 * @brief Specialized Entity designed to be controlled directly by the player
	 */
	class PlayerEntity : public Entity {
		/**
		 * Declare custom RTTI support
		 */
		TYPE_INFO_DECL(PlayerEntity)

	public:
		/**
		 * Constructor
		 */
		PlayerEntity();

		/**
		 * Injects and initializes an InputComponent to the entity's component list
		 */
		virtual void Initialize() override;

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

		/**
		 * Allows player entities to set up input components with keybindings
		 * @param component The component to configure
		 */
		virtual void SetupInputComponent(InputComponent* component) = 0;

	protected:
		/** Represents this entity's base movement speed */
		float MovementSpeed;
	};

}

