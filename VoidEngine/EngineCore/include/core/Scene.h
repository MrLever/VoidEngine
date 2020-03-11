#pragma once
//STD Headers
#include <memory>
#include <string>

//Library Headers

//Void Engine Headers
#include "math/Vector.h"

#include "core/Level.h"
#include "core/event_system/EventBusNode.h"
#include "core/event_system/events/WindowResizedEvent.h"
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
			EventBus* eventBus,
			std::shared_ptr<InputManager> inputManager,
			std::shared_ptr<PhysicsEngine> physicsEngine
		);
		~Scene();

		/**
		 * Allows node to receive and process events from EventBus
		 * @param event The event to process
		 */
		void ReceiveEvent(Event* event) override;

		void AddCamera(CameraComponent* camera);
		void RemoveCamera(CameraComponent* camera);
		void ActivateCamera(utils::Name cameraName);

		void BeginPlay();
		void ProcessInput(float deltaTime);
		void Update(float deltaTime);
		void Draw();

		/**
		 * Allows Entity to be spawned during playtime
		 */
		Entity* SpawnEntity(const utils::Name& type, Entity* parent = nullptr);

		/**
		 * Allows Entities to be removed from the simulation
		 */
		void DestroyEntity(Entity* entity);

		/**
		 * Allows the game to query the control file used for this level
		 * @return path relative to root of the level's keybinding file
		 */
		std::string GetControlFilePath() const;

	private:
		/**
		 * Scans scenes for light components and adds them to m_LightingEnviornment
		 */
		void GatherLights();

		std::string m_ControlFilePath;

		/** Maps Camera name to Camera to allow runtime lookup and switching */
		std::unordered_map<utils::Name, CameraComponent*> m_Cameras;

		/** Camera currently used to render the scene */
		CameraComponent* m_ActiveCamera;

		/** Entities active in scene simulation */
		std::vector<Entity*> m_Entities;

		/** Entities that will spawn at the end of the current frame */
		std::vector<Entity*> m_SpawnQueue;

		/** The input manager used to control entities in the scene */
		std::shared_ptr<InputManager> m_InputManager;

		/** The PhysicsEngine used to update the scene */
		std::shared_ptr<PhysicsEngine> m_PhysicsEngine;

		/** Used to maintain scene lighting data and pass to renderer */
		LightingEnvironment m_LightingEnvironment;
	};

}