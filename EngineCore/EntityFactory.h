#pragma once
//STD Headers
#include <memory>
#include <vector>
#include <string>

//Library Headers
#include "nlohmann/json.hpp"

//Void Engine Headers
#include "Entity.h"
#include "EntityData.h"
#include "ComponentFactory.h"
#include "ResourceAllocator.h"

namespace core {
	//Forward class declarations
	class Level;

	/**
	 * @class EntityFactory
	 * @brief Factory class to generate game enities from JSON data
	 */
	class EntityFactory	{
	public:
		/**
		 * Constructor
		 * @param currLevel The level this factory is coupled to
		 */
		EntityFactory(Level* currLevel);

		/**
		 * Function to create a set of entities from JSON data
		 * @param entityList The data for the entities to spawn
		 */
		void CreateEntities(const nlohmann::json& entityList);

		/**
		 * Function to create a single entity from JSON data
		 * @param entityData The data for a single entity
		 */
		[[nodiscard]] Entity* CreateEntity(const utils::Name& name, const std::string& type, const EntityData& data);

		/**
		 * Uses Entity data to apply location and rotation to an entity
		 * @param entityData The data to apply
		 * @param entity The entity to place
		 */
		void SetWorldOrientation(const nlohmann::json& levelData, core::Entity* entity);
	
	private:
		/** The current level using this factory */
		Level* CurrLevel;

		/** Factory to create components for entities */
		ComponentFactory CompFactory;
	};

}