#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "AudioManager.h"
#include "Configurable.h"
#include "Configuration.h"
#include "Console.h"
#include "EventBus.h"
#include "InputManager.h"
#include "ThreadPool.h"
#include "ResourceAllocator.h"
#include "Renderer.h"
#include "Level.h"
#include "MessageBus.h"
#include "Window.h"

namespace core {

	class Engine {
	public:
		/**
		 * Constructor
		 */
		Engine(const std::string& engineConfig);

		/**
		 * Instructs the engine to pump the event bus
		 */
		void DispatchEvents();

		/**
		 * Allows access the the game's thread pool
		 */
		ThreadPoolPtr GetThreadPool();

		/**
		 * Allows acces to the engine's event bus
		 */
		EventBusPtr GetEventBus();

		/**
		 * Allows access the the game's window manager
		 */
		WindowManagerPtr GetWindowManager();

		/**
		 * Allows access the the game's window manager
		 */
		InputManagerPtr GetInputManager();

		/**
		 * Get's the default level from engine configuration
		 */
		std::string GetDefaultLevel();

		/**
		 * Instructs the engine to pump the game window's message queue
		 */
		void PollInput();

		/**
		 * Instructs the engine to process input captured in the last polling
		 */
		void ProcessInput(Level* level, const float deltaTime);

		void SwapInputProfile(const std::string& profilePath);

		/**
		 * Instructs the engine to render the supplied level
		 */
		void Render(Level* level);

	private:
		/** A Handle to the Engine's thread pool */
		std::shared_ptr<utils::ThreadPool> GameThreadPool;

		/** Resource Manager for the engine's config files */
		std::shared_ptr<utils::ResourceAllocator<utils::Configuration>> ConfigManager;

		/** Engine's central event bus */
		std::shared_ptr<EventBus> GameEventBus;

		/** A handle to the game's display */
		std::shared_ptr<Window> GameWindow;

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
	};

}

