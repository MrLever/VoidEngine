#pragma once

//STD Headers
#include <chrono>
#include <memory>
#include <queue>
#include <stack>

//Library Headers

//Coati Headers
#include "Configurable.h"
#include "Configuration.h"
#include "EntityFactory.h"
#include "Engine.h"
#include "GameStateMachine.h"
#include "ThreadPool.h"
#include "ResourceAllocator.h"
#include "Level.h"
#include "MessageBus.h"

namespace core {

	//Forward Class declarations
	class WindowManager;
	class Renderer;
	class InputManager;
	class AudioManager;
	class Console;

	/**
	 * @class Game 
	 * @breif Framework that defines what a game is in the Void Engine
	 */
	class Game {
		using Timer = std::chrono::high_resolution_clock;

	public:
		/**
		 * Constructor
		 * @param name The game's name
		 */
		Game(const std::string& configFile);

		/**
		 * Destructor
		 */
		~Game();

	private:
		/**
		 * Instructs the game to update the entities in it's simulation
		 */
		void Update(float deltaTime);
		
		/**
		 * Instructs the game to process player input
		 * @param deltaTime the time step to use when applying user input
		 */
		void ProcessInput(float deltaTime);

		/**
		 * Runs the game simulation
		 */
		void ExecuteGameLoop();
	
		/**
		 * Tracks the game's frame rate.
		 * @param timeSinceLastFrame Time since the last frame, in seconds
		 */
		void UpdateFramerate(double timeSinceLastFrame);

		/**
		 * Set the game's current level
		 * @param newLevelPath path to the new level's data file
		 */
		void SetLevel(const std::string& newLevelPath);

		/** The game's current level */
		std::shared_ptr<Level> CurrentLevel;

		/** The game's engine */
		Engine GameEngine;

		/** Resource Manager for the engine's level files */
		ResourceAllocatorPtr<Level> LevelCache;

		/** The game's state machine */
		GameStateMachine StateMachine;

		/** The game's current framerate */
		int FrameRate;
	};

}