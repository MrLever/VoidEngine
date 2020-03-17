#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/gameplay_framework/entities/PlayerEntity.h"
#include "core/physics/components/PhysicsComponent.h"

namespace SuperVoid{

	/**
	 * @class PlayerShip
	 * @brief Represent's the player
	 */
	class PlayerShip : public core::PlayerEntity {
		TYPE_INFO_DECL(PlayerShip)
	public:
		/**
		 * Constructor
		 */
		PlayerShip();

		/**
		 * Allows an entity to configure itself after it is constructed
		 */
		virtual void Initialize() override;

		/**
		 * Allows player entities to set up input components with keybindings
		 * @param component The component to configure
		 */
		virtual void SetupInputComponent(core::InputComponent* component) override;
		
		/**
		 * Allows the pawn to float forward
		 */
		void MoveForward(float axisValue, float deltaTime);

		/**
		 * Allows the pawn to float right
		 */
		void MoveRight(float axisValue, float deltaTime);

	private:
		core::PhysicsComponent* m_RigidBody;
	};
}

