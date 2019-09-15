#pragma once

//STD Headers
#include <chrono>
#include <memory>
#include <queue>

//Library Headers

//Coati Headers
#include "Configurable.h"
#include "ThreadPool.h"
#include "ResourceManager.h"

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
		 * Instructs the InputManager to poll and process user input 
		 */
		void ProcessInput();

		/**
		 * Instructs entities to update themselves using the current time step
		 */
		void Update(double deltaSeconds);

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
		 */
		void UpdateFramerate(double timeSinceLastFrame);

	private:
		/** A Handle to the Engine's thread pool */
		std::shared_ptr<EngineUtils::ThreadPool> GameThreadPool;

		/** A handle to the Engine's resource manager */
		std::shared_ptr<EngineUtils::ResourceManager> GameResourceManager;

		/** A handle to the game's display */
		std::shared_ptr<WindowManager> Window;
		
		/** Pointer to the game's Rendering Engine */
		std::unique_ptr<Renderer> GameRenderer;

		/** Pointer to the game's Input Manager*/
		std::unique_ptr<InputManager> GameInputManager;

		/** Pointer to the game's Audio Manger */
		std::unique_ptr<AudioManager> GameAudioManager;
		
		/** The name displayed in the game window's title bar */
		std::string GameName;

		/** A queue of the last 10 frame durations for framerate calculations */
		std::queue<double> FrameQueue;

		/** The game's current framerate */
		int FrameRate;
	};

}