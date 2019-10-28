#pragma once

//STD Headers
#include <chrono>
#include <memory>
#include <queue>

//Library Headers

//Coati Headers
#include "Configuration.h"
#include "Engine.h"
#include "EventBusNode.h"
#include "ResourceAllocator.h"
#include "Level.h"
#include "WindowClosedEvent.h"
#include "PauseGameEvent.h"

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
		 * Runs the game simulation
		 */
		void ExecuteGameLoop();
		
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

		/** The game's current level */
		std::shared_ptr<Level> CurrentLevel;

		/** The game's engine */
		Engine GameEngine;

		/** Resource Manager for the engine's level files */
		ResourceAllocatorPtr<Level> LevelCache;

		/** The game's current framerate */
		int FrameRate;

		/** Flag to determine when the game loop should terminate */
		bool Terminated;

		/** Flag to query whether the game is paused */
		bool Paused;

		/**
		 * Helper class to connect Game to the event bus
		 */
		class GameEventBusNode : EventBusNode {
		public:
			/**
			 * Constructor
			 */
			GameEventBusNode(EventBus* bus, Game* owner) 
				: EventBusNode(bus), Owner(owner) {

			}

			/**
			 * Function to dispatch events to Game
			 */
			virtual void ReceiveEvent(Event* event) {
				EventDispatcher dispatcher(event);
				
				dispatcher.Dispatch<WindowClosedEvent>(
					[this](WindowClosedEvent* windowEvent) {
						Owner->HandleWindowClosed(windowEvent);
					}
				);

				dispatcher.Dispatch<PauseGameEvent>(
					[this](PauseGameEvent* pauseEvent) {
						Owner->PauseGame(pauseEvent);
					}
				);

			}

			Game* Owner;
		};

		std::unique_ptr<GameEventBusNode> BusNode;

	};

}