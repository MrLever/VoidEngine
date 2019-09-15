#pragma once
//STD Headers
#include <string>
#include <memory>
#include <vector>

//Library Headers
#include "nlohmann/json.hpp"

//Void Engine Headers
#include "Name.h"
#include "Resource.h"
#include "Entity.h"

namespace EngineCore {

	/**
	 * @class Level
	 * @brief Class to represent a level in the game
	 */
	class Level : public EngineUtils::Resource {
	
	public:
		/**
		 * Constructor
		 */
		Level(const std::string& levelPath);

		/**
		 * Destructor
		 */
		~Level();

		/**
		 * Loads level JSON data from main memory
		 * @return whether the load was successful
		 */
		bool Load() override;

		/**
		 * Loads an error level to signify invalid resource location
		 * @return whether the operation was a success
		 */
		bool LoadErrorResource() override;

		/**
		 * Getter for level's name
		 * @return The level's name
		 */
		EngineUtils::Name GetName();

		/**
		 * Instructs all entities in level to begin play
		 */
		void BeginPlay();

		/**
		 * Updates all the entities in the level
		 * @param deltaTime time elapsed since last update
		 */
		void Update(double deltaTime);

		/**
		 * Function to get entity data to send to an entity factory for contruction
		 */
		nlohmann::json GetEntityData();

	private:
		/** All the entities spawned in the level */
		std::vector<Entity*> Entities;

		/** JSON representation of the level, loaded from main memory */
		nlohmann::json LevelData;

		/** The level's name */
		EngineUtils::Name LevelName;
	};

}