#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Logger.h"

namespace core {
	//Forward class declarations
	class Game;

	/**
	 * @class GameState
	 * @brief Used to control execution of the game loop
	 */
	class GameState {
	public:
		/**
		 * Constructor
		 */
		GameState(Game* owner);

		/**
		 * Defines what should happen when this state is entered
		 */
		virtual void Enter() = 0;

		/**
		 * Defines how the game should update when this state is selected
		 * @param deltaTime The time step to use for updates
		 */
		virtual void Update(float deltaTime) = 0;

		/**
		 * Defines what should happen when this state is exited
		 */
		virtual void Exit() = 0;

	protected:
		Game* Owner;
	};
}
