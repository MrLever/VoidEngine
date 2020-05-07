#pragma once
//STD Headers
#include <memory>
#include <string>
#include <list>

//Library Headers
#include <math/Vector.h>

//Void Engine Headers
#include "utils/resource/JsonResource.h"

#include "core/Level.h"
#include "core/event_system/EventSystem.h"
#include "core/event_system/events/WindowResizedEvent.h"
#include "core/gameplay_framework/Prototype.h"
#include "core/input/InputManager.h"
#include "core/input/ControlLayout.h"
#include "core/rendering/Renderer.h"
#include "core/rendering/LightingEnvironment.h"
#include "core/rendering/components/CameraComponent.h"
#include "core/physics/PhysicsEngine.h"

namespace core {

	class Scene : EventListener {
	public:
		/**
		 * Constructor
		 * @param levelPath The location of the level's resource path
		 * @param renderer The renderer used for this Scene
		 * @param physicsEngine the Physics Engine used to update rigid bodies in the scene
		 */
		Scene(
			const std::string& levelPath,
			EventSystem* eventSystem,
			std::shared_ptr<InputManager> inputManager,
			std::shared_ptr<PhysicsEngine> physicsEngine
		);

		/**
		 * Destructor
		 */
		~Scene();

		void ActivateCamera(CameraComponent* camera);
		void RemoveCamera(CameraComponent* camera);

		/** 
		 * Triggers begin play on all entities
		 */
		void BeginPlay();
		void ProcessInput(float deltaTime);
		void Update(float deltaTime);
		void Draw();

		void RestartLevel();

		/**
		 * Allows entities to construct entities from prototypes at runtime
		 */
		Entity* SpawnEntity(const Prototype& prototype,	Entity* parent = nullptr);

		/**
		 * Allows entities to construct entities from prototypes at runtime
		 */
		Entity* SpawnEntity(
			const Prototype& prototype, 
			const Transform& transform,
			Entity* parent = nullptr
		);

		/**
		 * Defualt constructs an entity of type T
		 */
		template <class T>
		T* SpawnEntity(Entity* parent, const Transform& transform = Transform());

		/**
		 * Transfers ownership of child's unqique pointer to parent
		 */
		void Reparent(Entity* child, Entity* parent);

		/**
		 * Allows Entities to be removed from the simulation
		 */
		void Destroy(Entity* entity);

		/**
		 * Allows the game to query the control file used for this level
		 * @return path relative to root of the level's keybinding file
		 */
		std::string GetControlFilePath() const;

		/**
		 * Allows user code to search scene for all components of specified type
		 * @return vector of discovered components
		 */
		template<class T>
		std::vector<T*> FindComponentsOfType();

		/**
		 * Allows entities to ask for other entities by ID
		 */
		Entity* FindEntityByID(unsigned ID);

	private:
		/**
		 */
		void SpawnInitialScene();

		/** 
		 * Adds root entities from the spawn queue into the entity vector 
		 */
		void ProcessSpawnQueue();

		/**
		 * Destroys all entities in the destruction queue
		 */
		void ProcessDestructionQueue();

		/**
		 * Recursive helper function to spawn entity given data
		 */
		std::unique_ptr<Entity> SpawnEntity(const nlohmann::json& entityData);

		/** Root entities active in scene simulation */
		std::vector<std::unique_ptr<Entity>> entities;

		/** 
		 * Entities Instantiated during runtime are added the the scene heirarchy 
		 * at the end of the frame they were spawned on.
		 */
		std::vector<std::pair<std::unique_ptr<Entity>, Entity*>> spawnQueue;

		/** json definition of level intitial condition */
		std::shared_ptr<utils::JsonResource> levelData;

		/** Entities marked for destruction are destroyed at the end of the current frame */
		std::unordered_set<Entity*> destructionQueue;

		/** Path to the level's control bindings */
		std::string controlFilePath;

		/** Maps Camera name to Camera to allow runtime lookup and switching */
		std::vector<CameraComponent*> cameras;

		/** Camera currently used to render the scene */
		CameraComponent* activeCamera;

		/** The input manager used to control entities in the scene */
		std::shared_ptr<InputManager> inputManager;

		/** The PhysicsEngine used to update the scene */
		std::shared_ptr<PhysicsEngine> physicsEngine;

		/** Used to maintain scene lighting data and pass to renderer */
		LightingEnvironment m_LightingEnvironment;

		bool reset;

		/** Data cache for already loaded level data */
		static utils::ResourceAllocator<utils::JsonResource> s_LevelCache;
	};

	template<class T>
	inline T* Scene::SpawnEntity(Entity* parent, const Transform& transform) {
		auto entityHandle = std::make_unique<T>();
		auto weakPtr = entityHandle.get();

		entityHandle->transform = transform;
		entityHandle->Initialize();
		spawnQueue.push_back({ std::move(entityHandle), parent });

		return weakPtr;
	}

	template<class T>
	inline std::vector<T*> Scene::FindComponentsOfType(){
		std::vector<T*> searchResults;

		for (auto& entity : entities) {
			auto components = entity->GetComponents<T>();
			searchResults.insert(searchResults.end(), components.begin(), components.end());
			entity->GetComponentsInChildren<T>(searchResults);
		}

		return searchResults;
	}

}