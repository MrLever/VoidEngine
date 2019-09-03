#pragma once
//STD Headers
#include <memory>
#include <vector>

//Library Headers


//Void Engine Headers
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

	protected:
		std::vector<std::shared_ptr<Entity>> Entities;

	};

}