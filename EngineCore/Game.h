#pragma once

//STD Headers
#include <chrono>
#include <memory>
#include <queue>

//Library Headers

//Coati Headers
#include "Configurable.h"
#include "EntityFactory.h"
#include "ThreadPool.h"
#include "ResourceManager.h"
#include "Level.h"
#include "MessageBus.h"

namespace EngineCore {

	//Forward Class declarations
	class WindowManager;
	class Renderer;
	class InputManager;
	class AudioManager;
	class Console;

	/**
	 * @class Game Framework that defines what a game is in the Void Engine
	 */
	class Game {
		using Timer = std::chrono::high_resolution_clock;

	public:
		/**
		 * Constructor
		 * @param name The game's name
		 */
		Game(const std::string& name);

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
		 * Instructs entities to update themselves using the current time step
		 * @param deltaTime Time since the last update in seconds
		 */
		void Update(double deltaTime);

		/**
		 * Instruct the renderer to draw the current scene
		 */
		void Render();

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

	private:
		/** The game's current level */
		std::shared_ptr<Level> CurrentLevel;

		/** Entity factory used by levels to generate a scene */
		std::shared_ptr<EntityFactory> GameEntityFactory;

		/** A Handle to the Engine's thread pool */
		std::shared_ptr<EngineUtils::ThreadPool> GameThreadPool;

		/** A handle to the Engine's resource manager */
		std::shared_ptr<EngineUtils::ResourceManager> GameResourceManager;

		/** A handle to the game's display */
		std::shared_ptr<WindowManager> Window;

		/** The game's message bus */
		std::shared_ptr<MessageBus> GameMessageBus;

		/** The game's console */
		std::shared_ptr<Console> GameConsole;
		
		/** Pointer to the game's Rendering Engine */
		std::unique_ptr<Renderer> GameRenderer;

		/** Pointer to the game's Input Manager*/
		std::unique_ptr<InputManager> GameInputManager;

		/** Pointer to the game's Audio Manger */
		std::unique_ptr<AudioManager> GameAudioManager;
		
		/** The name displayed in the game window's title bar */
		std::string GameName;

		/** The game's current framerate */
		int FrameRate;
	};

}