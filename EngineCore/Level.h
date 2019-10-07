#pragma once
//STD Headers
#include <string>
#include <memory>
#include <vector>

//Library Headers
#include <nlohmann/json.hpp>

//Void Engine Headers
#include "EntityFactory.h"
#include "EntityData.h"
#include "Name.h"
#include "ResourceAllocator.h"
#include "Resource.h"

namespace core {

	/**
	 * @class Level
	 * @brief Class to represent a level in the game
	 */
	class Level : public utils::Resource {
		friend class EntityFactory;
		friend class ComponentFactory;

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
		 * Loads and spawns entities into the level
		 */
		virtual void Initialize() override;

	    /**
		 * Getter for level's name
		 * @return The level's name
		 */
		utils::Name GetName();

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
		 * Function to get the current scene of drawables
		 * @return All the drawable objects in the scene
		 */
		std::vector<Entity*> GetScene();

	private:
		ResourceAllocatorPtr<EntityData> EntityDataCache;
		ResourceAllocatorPtr<Texture> TextureCache;

		/** Factory object used to add entities to this level's scene */
		EntityFactory* LevelEntityFactory;

		/** All the entities spawned in the level */
		std::vector<Entity*> Entities;

		/** JSON representation of the level, loaded from main memory */
		nlohmann::json LevelData;

		/** The level's name */
		utils::Name LevelName;
	};

}