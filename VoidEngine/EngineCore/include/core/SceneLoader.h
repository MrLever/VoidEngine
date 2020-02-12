#pragma once
//STD Headers
#include <string>
#include <memory>
#include <vector>

//Library Headers


//Void Engine Headers
#include "utils/Name.h"
#include "utils/factory/Factory.h"
#include "utils/resource/ResourceAllocator.h"

#include "core/Scene.h"
#include "core/Level.h"
#include "core/gameplay_framework/Entity.h"
#include "core/rendering/Model.h"

namespace core {
	/**
	 * @class SceneLoader
	 * @brief Builder class used to load Level data into a scene 
	 */
	class SceneLoader {
	public:
		/**
		 * Constructor
		 */
		SceneLoader();

		/**
		 * Destructor
		 */
		~SceneLoader();

		/**
		 * Loads level data file located at levelPath and initializes scene
		 * @param scene The scene to populate
		 * @param levelPath The level file to load
		 */
		void LoadLevel(Scene* scene, const std::string& levelPath);

	private:
		/** Data cache for already loaded level data */
		utils::ResourceAllocator<Level> LevelCache;
	};
}