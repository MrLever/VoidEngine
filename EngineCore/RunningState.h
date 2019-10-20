#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "GameState.h"

namespace core {

	class RunningState : public GameState {
	public:
		/**
		 * Constructor
		 */
		RunningState(Game* owner);

		/**
		 * Defines what should happen when this state is entered
		 */
		void Enter() override;

		/**
		 * Defines how the game should update when this state is selected
		 * @param deltaTime The time step to use for updates
		 */
		void Update(float deltaTime) override;

		/**
		 * Defines what should happen when this state is exited
		 */
		void Exit() override;
	};

}
