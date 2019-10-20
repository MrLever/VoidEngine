#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "GameState.h"

namespace core {

	class PauseState : public GameState {
	public: 
		/**
		* Defines what should happen when this state is entered
		*/
		void Enter() override;

		/**
		 * Defines how the game should update when this state is selected
		 * @param deltaTime The time step to use for updates
		 */
		void Update(Level* currentLevel, const float deltaTime) override;

		/**
		 * Defines what should happen when this state is exited
		 */
		void Exit() override;
	};

}
