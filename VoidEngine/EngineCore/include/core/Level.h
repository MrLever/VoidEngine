#pragma once
//STD Headers
#include <string>
#include <memory>
#include <vector>

//Library Headers
#include <nlohmann/json.hpp>

//Void Engine Headers
#include "utils/Name.h"
#include "utils/factory/Factory.h"
#include "utils/resource/ResourceAllocator.h"
#include "utils/resource/JsonResource.h"

#include "core/gameplay_framework/EntityData.h"
#include "core/gameplay_framework/Entity.h"
#include "core/rendering/Model.h"

namespace core {

	/**
	 * @class Level
	 * @brief Class to represent a level in the game
	 */
	class Level : public utils::JsonResource {
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
		 * Loads an error level to signify invalid resource location
		 * @return whether the operation was a success
		 */
		bool LoadErrorResource() override;

		/**
		 * Loads and spawns entities into the level
		 */
		virtual void Initialize() override;

		/**
		 * Getter for level's name
		 * @return The level's name
		 */
		utils::Name GetName();

	private:
		/** The level's name */
		utils::Name LevelName;

	};

}