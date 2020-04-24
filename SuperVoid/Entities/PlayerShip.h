#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/gameplay_framework/Prototype.h"
#include "core/gameplay_framework/entities/PlayerEntity.h"
#include "core/physics/components/PhysicsComponent.h"

namespace SuperVoid {

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
		
		virtual void Tick(float deltaTime) override;

		/**
		 * Allows the pawn to float forward
		 */
		void MoveForward(float axisValue, float deltaTime);

		/**
		 * Allows the pawn to float right
		 */
		void MoveRight(float axisValue, float deltaTime);

		/**
		 * Rotates the ship left and right
		 */
		void Rotate(float axisValue, float deltaTime);

		void Fire();

	private:
		core::Prototype m_BulletPrototype;
		core::PhysicsComponent* m_RigidBody;


		float m_EngineStrength;
	};
}

