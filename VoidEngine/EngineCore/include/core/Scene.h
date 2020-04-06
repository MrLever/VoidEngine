#pragma once
//STD Headers
#include <memory>
#include <string>

//Library Headers
#include <math/Vector.h>

//Void Engine Headers
#include "utils/resource/JsonResource.h"

#include "core/Level.h"
#include "core/event_system/EventBusNode.h"
#include "core/event_system/events/WindowResizedEvent.h"
#include "core/gameplay_framework/Prototype.h"
#include "core/input/InputManager.h"
#include "core/input/ControlLayout.h"
#include "core/rendering/Renderer.h"
#include "core/rendering/LightingEnvironment.h"
#include "core/rendering/components/CameraComponent.h"
#include "core/physics/PhysicsEngine.h"

namespace core {

	class Scene : EventBusNode {
		friend class SceneLoader;
	public:
		/**
		 * Constructor
		 * @param renderer The renderer used for this Scene
		 * @param physicsEngine the Physics Engine used to update rigid bodies in the scene
		 */
		Scene(
			const std::string& levelPath,
			EventBus* eventBus,
			std::shared_ptr<InputManager> inputManager,
			std::shared_ptr<PhysicsEngine> physicsEngine
		);

		/**
		 * Destructor
		 */
		~Scene();

		/**
		 * Allows node to receive and process events from EventBus
		 * @param event The event to process
		 */
		void ReceiveEvent(Event* event) override;

		void ActivateCamera(CameraComponent* camera);
		void RemoveCamera(CameraComponent* camera);

		void BeginPlay();
		void ProcessInput(float deltaTime);
		void Update(float deltaTime);
		void Draw();

		/**
		 * Allows entities to construct entities from prototypes at runtime
		 */
		Entity* Instantiate(const Prototype& prototype, Entity* parent = nullptr);

		/**
		 * Allows Entities to be removed from the simulation
		 */
		void DestroyEntity(Entity* entity);

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

	private:
		/**
		 * Recursive helper function to spawn entity given data
		 */
		std::unique_ptr<Entity> SpawnEntity(const nlohmann::json& entityData);

		std::string m_ControlFilePath;

		/** Maps Camera name to Camera to allow runtime lookup and switching */
		std::vector<CameraComponent*> m_Cameras;

		/** Camera currently used to render the scene */
		CameraComponent* m_ActiveCamera;

		/** Entities active in scene simulation */
		std::vector<std::unique_ptr<Entity>> m_Entities;

		/** Entities that will spawn at the end of the current frame */
		std::vector<std::unique_ptr<Entity>> m_SpawnQueue;

		/** The input manager used to control entities in the scene */
		std::shared_ptr<InputManager> m_InputManager;

		/** The PhysicsEngine used to update the scene */
		std::shared_ptr<PhysicsEngine> m_PhysicsEngine;

		/** Used to maintain scene lighting data and pass to renderer */
		LightingEnvironment m_LightingEnvironment;

		/** Data cache for already loaded level data */
		static utils::ResourceAllocator<utils::JsonResource> s_LevelCache;
	};

	template<class T>
	inline std::vector<T*> Scene::FindComponentsOfType(){
		std::vector<T*> searchResults;

		for (auto& entity : m_Entities) {
			auto components = entity->GetComponents<T>();
			searchResults.insert(searchResults.end(), components.begin(), components.end());
			entity->GetComponentsInChildren<T>(searchResults);
		}

		return searchResults;
	}

}