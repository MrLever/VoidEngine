#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/gameplay_framework/entities/PlayerEntity.h"

namespace core {

	class Observer : public PlayerEntity {
		/**
		 * Declare custom RTTI support
		 */
		TYPE_INFO_DECL(Observer)
	
	public:
		/**
		 * Constructor
		 */
		Observer();

		/**
		 * Destructor
		 */
		~Observer() override;

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
		virtual void SetupInputComponent(InputComponent* component) override;


	private:
		/** 
		 * Allows the pawn to float forward 
		 */
		void MoveForward(float axisValue, float deltaTime);

		/**
		 * Allows the pawn to float right
		 */
		void MoveRight(float axisValue, float deltaTime);

		/**
		 * Allows the pawn to change it's look direction
		 */
		void LookUp(float axisValue, float deltaTime);

		/**
		 * Allows the pawn to change it's look direction
		 */
		void LookRight(float axisValue, float deltaTime);

	};

}
