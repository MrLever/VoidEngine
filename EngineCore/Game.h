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
#include "GameState.h"
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
		 * Initializes all of the game's major utilities and core systems
		 */
		void InitGame();

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

		/** A Handle to the Engine's thread pool */
		std::shared_ptr<utils::ThreadPool> GameThreadPool;

		/** Resource Manager for the engine's config files */
		std::shared_ptr<utils::ResourceAllocator<utils::Configuration>> ConfigManager;

		/** Resource Manager for the engine's level files */
		ResourceAllocatorPtr<Level> LevelCache;

		/** A handle to the game's display */
		std::shared_ptr<WindowManager> Window;

		/** The game's message bus */
		std::shared_ptr<MessageBus> GameMessageBus;

		/** The game's console */
		std::shared_ptr<Console> GameConsole;
		
		/** Pointer to the game's Input Manager*/
		std::shared_ptr<InputManager> GameInputManager;

		/** Pointer to the game's Rendering Engine */
		std::unique_ptr<Renderer> GameRenderer;

		/** Pointer to the game's Audio Manger */
		std::unique_ptr<AudioManager> GameAudioManager;
		
		/** Config settings for the game */
		utils::Configuration EngineConfig;

		/** The game's state machine */
		std::stack<GameState> GameStateMachine;

		/** The game's current framerate */
		int FrameRate;
	};

}