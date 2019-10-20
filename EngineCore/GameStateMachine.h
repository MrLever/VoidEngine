#pragma once
//STD Headers
#include <memory>
#include <stack>

//Library Headers

//Void Engine Headers
#include "Level.h"

namespace core {
	//Forward class declarations
	class Game;
	class GameState;
	/**
	 * @class GameStateMachine
	 * @brief Stack-based machine for managing game states.
	 */
	class GameStateMachine {
	public:
		/**
		 * Constructor
		 */
		GameStateMachine(Game* owner);

		/**
		 * Instructs the machine to run the current state's update function
		 * @param deltaTime The time step for the current update
		 */
		void Update(Level* currLevel, const float deltaTime);

		/**
		 * Push a state onto the state machine
		 * @param state The state to add
		 */
		void PushState(std::unique_ptr<GameState> state);

		/**
		 * Pop the current state off the stack
		 */
		void PopState();

	private:
		/** The game that owns this state machine */
		Game* Owner;

		/** The stack used to manage state history */
		std::stack<std::unique_ptr<GameState>> StateMachine;
	};

}
