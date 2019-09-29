#pragma once
//STD Headers
#include <memory>
#include <vector>
#include <string>

//Library Headers
#include "nlohmann/json.hpp"

//Void Engine Headers
#include "Entity.h"
#include "ComponentFactory.h"
#include "GraphicsComponent.h"

namespace EngineCore {
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
		void CreateEntityList(const nlohmann::json& entityList);

		/**
		 * Function to create a single entity from JSON data
		 * @param entityData The data for a single entity
		 */
		[[nodiscard]] Entity* CreateEntity(const nlohmann::json& entityData);

		void SetWorldOrientation(const nlohmann::json& entityData, EngineCore::Entity* entity);
	
	private:
		/** The current level using this factory */
		Level* CurrLevel;

		/** Factory to create components for entities */
		ComponentFactory CompFactory;
	};

}