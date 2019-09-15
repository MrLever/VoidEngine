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
	class Level {
	
	public:
		/**
		 * Constructor
		 */
		Level();

		/**
		 * Destructor
		 */
		~Level();

		/**
		 * Getter for level's name
		 * @return The level's name
		 */
		EngineUtils::Name GetName();

	private:
		/** All the entities spawned in the level */
		std::vector<Entity*> Entities;

		/** JSON representation of the level, loaded from main memory */
		nlohmann::json LevelData;

		/** The level's name */
		EngineUtils::Name LevelName;
	};

}