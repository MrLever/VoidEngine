#pragma once
//STD Headers
#include <vector>
#include <memory>

//Library Headers

//Void Engine Headers
#include "Entity.h"

namespace EngineCore {
	/**
	 * @class The SceneMangager is responsible for managing active game entities in the simulation
	 */
	class SceneManager {
	public:
		/**
		 * Constructor
		 */
		SceneManager();

		/**
		 * Instructs the SceneManager to update all entities in the scene
		 * @param deltaTime Time since the last update
		 */
		void UpdateScene(double deltaTime);

		void DrawScene();

		void StartLevel();

	private:
		std::vector<std::shared_ptr<Entity>> Entities;
	};

}