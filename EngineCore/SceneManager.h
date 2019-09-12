#pragma once
//STD Headers
#include <vector>
#include <memory>

//Library Headers

//Void Engine Headers
#include "Entity.h"
#include "Level.h"

//Forward class definitions
namespace EngineUtils {
	class ThreadPool;
	class ResourceManager;
}

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
		SceneManager(
			std::shared_ptr<EngineUtils::ThreadPool> pool, 
			std::shared_ptr<EngineUtils::ResourceManager> resourceManager
		);

		/**
		 * Destructor
		 */
		~SceneManager();

		/**
		 * Loads level to prepare it for gameplay
		 */
		void LoadLevel(const Level& level);

		/**
		 * Instructs every Enity to perform it's BeginPlay logic
		 */
		void StartLevel();

		/**
		 * Instructs the SceneManager to update all entities in the scene
		 * @param deltaTime Time since the last update
		 */
		void UpdateScene(double deltaTime);


		/**
		 * Member function to allow access the the current scene
		 * @return The current scene
		 */
		std::vector<std::shared_ptr<Entity>> GetScene();

	private:
		/** List of all the Entities present in the scene */
		std::vector<std::shared_ptr<Entity>> Entities;

		/** The game's active thread pool */
		std::shared_ptr<EngineUtils::ThreadPool> GameThreadPool;

		/** The game's active resource manager */
		std::shared_ptr<EngineUtils::ResourceManager> GameResourceManager;
	};

}