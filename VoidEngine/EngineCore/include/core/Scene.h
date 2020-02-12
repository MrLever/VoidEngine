#pragma once
//STD Headers
#include <memory>
#include <string>

//Library Headers

//Void Engine Headers
#include "core/rendering/Renderer.h"
#include "core/rendering/components/CameraComponent.h"

#include "core/physics/PhysicsEngine.h"

#include "core/Level.h"

namespace core {

	class Scene {
	public:
		/**
		 * Constructor
		 * @param renderer The renderer used for this Scene
		 * @param physicsEngine the Physics Engine used to update rigid bodies in the scene
		 */
		Scene(std::shared_ptr<Renderer> renderer, std::shared_ptr<PhysicsEngine> physicsEngine);
		~Scene();

		void AddCamera(CameraComponent* camera);
		void RemoveCamera(CameraComponent* camera);
		void ActivateCamera(utils::Name cameraName);

		void Load();
		void BeginPlay();
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

	private:
		/** Maps Camera name to Camera to allow runtime lookup and switching */
		std::unordered_map<utils::Name, CameraComponent*> Cameras;

		/** Entities active in scene simulation */
		std::vector<Entity*> Entities;

		/** The renderer used to draw the scene */
		std::shared_ptr<Renderer> SceneRenderer;

		/** The PhysicsEngine used to update the scene */
		std::shared_ptr<PhysicsEngine> ScenePhysicsEngine;
	
	};

}