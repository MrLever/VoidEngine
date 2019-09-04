#pragma once

//STD Headers
#include <chrono>
#include <memory>
#include <vector>

//Library Headers

//Project-Coati Headers
#include "Console.h"
#include "SceneManager.h"
#include "MessageBus.h"

namespace EngineCore {

	//Forward Class declarations
	class MessageBus;

	/**
	 * @class World The World is responsible for defining time and space in the simulation
	 */
	class World {
	public:
		/**
		 * Constructor
		 */
		World();
		
		/**
		 * Destructor
		 */
		~World();

		/**
		 * Instructs the world to update the simulation
		 */
		void Update(double deltaSeconds);

		/**
		 * Instructs the world to get the current scene for rendering
		 */
		std::vector<std::shared_ptr<Entity>> GetCurrentScene();

	private:
		/** Message Bus used to coordinate game events */
		std::shared_ptr<MessageBus> GameMessageBus;
		
		/** Scene Manager used to coordinate the entities in the simulation */
		std::shared_ptr<SceneManager> GameSceneManager;

		/** The Debug Console used */
		std::shared_ptr<Console> GameConsole;
	};

}