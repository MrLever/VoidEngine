#pragma once
//STD Headers
#include <memory>
#include <string>

//Library Headers

//Void Engine Headers
#include "core/input/InputManager.h"
#include "core/input/ControlLayout.h"
#include "core/rendering/Renderer.h"
#include "core/rendering/components/CameraComponent.h"
#include "core/physics/PhysicsEngine.h"
#include "core/Level.h"

namespace core {

	class Scene {
		friend class SceneLoader;
	public:
		/**
		 * Constructor
		 * @param renderer The renderer used for this Scene
		 * @param physicsEngine the Physics Engine used to update rigid bodies in the scene
		 */
		Scene(
			std::shared_ptr<InputManager> inputManager,
			std::shared_ptr<Renderer> renderer, 
			std::shared_ptr<PhysicsEngine> physicsEngine
		);
		~Scene();

		void AddCamera(CameraComponent* camera);
		void RemoveCamera(CameraComponent* camera);
		void ActivateCamera(utils::Name cameraName);

		void BeginPlay();
		void ProcessInput(float deltaTime);
		void Update(float deltaTime);
		void Draw() const;

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
		std::string ControlFilePath;

		/** Maps Camera name to Camera to allow runtime lookup and switching */
		std::unordered_map<utils::Name, CameraComponent*> Cameras;

		/** Entities active in scene simulation */
		std::vector<Entity*> Entities;

		/** Entities that will spawn at the end of the current frame */
		std::vector<Entity*> EntitiesToSpawn;

		/** The input manager used to control entities in the scene */
		std::shared_ptr<InputManager> SceneInputManager;

		/** The renderer used to draw the scene */
		std::shared_ptr<Renderer> SceneRenderer;

		/** The PhysicsEngine used to update the scene */
		std::shared_ptr<PhysicsEngine> ScenePhysicsEngine;

	};

}