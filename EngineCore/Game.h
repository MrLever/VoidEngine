#pragma once

//STD Headers
#include <chrono>
#include <memory>
#include <queue>

//Library Headers

//Coati Headers
#include "Configurable.h"

namespace EngineCore {

	//Forward Class declarations
	class MessageBus;
	class WindowManager;

	class World;
	class Renderer;
	class InputManager;
	class AudioManager;
	class Console;


	class Game {
		using Timer = std::chrono::high_resolution_clock;

	public:
		/**
		 * Constructor
		 * @param name The game's name
		 */
		Game(std::string name);
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
		/** The Message bus used to pass events through the simulation */
		std::shared_ptr<MessageBus> GameMessageBus;

		/** A handle to the game's display */
		std::shared_ptr<WindowManager> Window;

		/** Pointer to the game's Rendering Engine */
		std::unique_ptr<Renderer> GameRenderer;

		/** Pointer to the game's Input Manager*/
		std::unique_ptr<InputManager> GameInputManager;

		/** Pointer to the game's Audio Manger */
		std::unique_ptr<AudioManager> GameAudioManager;

		/** Reference to the currently active game space */
		std::unique_ptr<World> GameWorld;
		
		/** Pointer to the game's active debug console object */
		std::unique_ptr<Console> GameConsole;

		/** The name displayed in the game window's title bar */
		std::string GameName;

		/** A queue of the last 10 frame durations for framerate calculations */
		std::queue<double> FrameQueue;

		/** The game's current framerate */
		int FrameRate;
	};

}