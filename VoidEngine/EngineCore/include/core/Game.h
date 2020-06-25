#pragma once

//STD Headers
#include <chrono>
#include <memory>
#include <queue>

//Library Headers

//Void Engine Headers
#include "utils/configuration/Configurable.h"
#include "utils/configuration/Configuration.h"
#include "utils/threading/ThreadPool.h"
#include "utils/resource/ResourceAllocator.h"
#include "utils/Logger.h"

#include "core/Window.h"
#include "core/audio/AudioManager.h"
#include "core/event_system/EventSystem.h"
#include "core/event_system/events/WindowClosedEvent.h"
#include "core/input/InputManager.h"
#include "core/physics/PhysicsEngine.h"
#include "core/rendering/Renderer.h"
#include "core/event_system/events/PauseGameEvent.h"
#include "core/event_system/events/InputActionEvent.h"

namespace core {
	/**
	 * @class Game 
	 * @brief Framework that defines what a game is in the Void Engine
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
		 * Set's up game engine enviornment
		 */
		void Initialize();

		/**
		 * Runs the game simulation
		 */
		void ExecuteGameLoop();
		
		/**
		 * Instructs the game to update the entities in it's simulation
		 */
		void Update(float deltaTime);
		
		/**
		 * Tracks the game's frame rate.
		 * @param timeSinceLastFrame Time since the last frame, in seconds
		 */
		void UpdateFramerate(double timeSinceLastFrame);

		/**
		 * Allows the game to react to WindowClosedEvents
		 */
		void HandleWindowClosed(WindowClosedEvent* event);
		
		/**
		 * Allows the game to react to PauseGameEvents
		 */
		void PauseGame(PauseGameEvent* event);

		/**
		 * Set the game's current level
		 * @param newLevelPath path to the new level's data file
		 */
		void SetLevel(const std::string& newLevelPath);

		/** The game's active scene */
		std::unique_ptr<Scene> m_Scene;
		
		/** A Handle to the Engine's thread pool */
		std::shared_ptr<utils::ThreadPool> m_ThreadPool;

		/** Resource Manager for the engine's config files */
		utils::ResourceAllocator<utils::Configuration> m_ConfigCache;

		utils::Configuration m_EngineConfig;

		/** Engine's central event bus */
		std::unique_ptr<EventSystem> m_EventSystem;

		/** A handle to the game's display */
		std::shared_ptr<Window> m_Window;

		/** Pointer to the game's Input Manager*/
		std::shared_ptr<InputManager> m_InputManager;

		/** Pointer to physics subsystem */
		std::shared_ptr<PhysicsEngine> m_PhysicsEngine;
		
		/** Pointer to the game's Audio Manger */
		std::unique_ptr<AudioManager> m_AudioManager;

		/** Event listener as component */
		std::unique_ptr<EventListener> m_EventListener;

		/** Flag to determine when the game loop should terminate */
		bool m_IsTerminated;

		/** Flag to query whether the game is paused */
		bool m_IsPaused;

	};

}