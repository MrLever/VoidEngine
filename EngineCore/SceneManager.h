#pragma once
//STD Headers
#include <vector>
#include <memory>

//Library Headers

//Void Engine Headers
#include "Entity.h"

namespace EngineCore {
	/**
	 * @class SceneManager
	 * @brief The SceneMangager is responsible for managing active game entities in the simulation
	 */
	class SceneManager {
	public:
		/**
		 * Constructor
		 */
		SceneManager();

		/**
		 * Destructor
		 */
		~SceneManager();

		/**
		 * Instructs the SceneManager to update all entities in the scene
		 * @param deltaTime Time since the last update
		 */
		void UpdateScene(double deltaTime);

		/**
		 * Instructs every Enity to perform it's BeginPlay logic
		 */
		void StartLevel();

		/**
		 * Member function to allow access the the current scene
		 * @return The current scene
		 */
		std::vector<std::shared_ptr<Entity>> GetScene();

	private:
		/** List of all the Entities present in the scene */
		std::vector<std::shared_ptr<Entity>> Entities;
	};

}