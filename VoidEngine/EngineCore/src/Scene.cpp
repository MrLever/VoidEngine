#include "..\include\core\Scene.h"
//STD Headers

//Library Headers

//Void Engine Headers

namespace core {
	Scene::Scene(std::shared_ptr<Renderer> renderer, std::shared_ptr<PhysicsEngine> physicsEngine) 
		: SceneRenderer(renderer), ScenePhysicsEngine(physicsEngine) {

	}

	Scene::~Scene() {
		for (auto& entity : Entities) {
			delete entity;
			entity = nullptr;
		}
	}
	
	void Scene::AddCamera(CameraComponent* camera) {
		SceneRenderer->InitializeCamera(camera);
		Cameras.insert({camera->GetName(), camera});
	}

	void Scene::RemoveCamera(CameraComponent* camera) {
		Cameras.erase(camera->GetName());
	}

	void Scene::ActivateCamera(utils::Name cameraName) {
		if (Cameras.find(cameraName) == Cameras.end()) {
			utils::Logger::LogError("Camera " + cameraName.StringID + " not found. Camara not activated");
			return;
		}

		SceneRenderer->UseCamera(Cameras[cameraName]);
	}
	
	void Scene::Load() {
		;
	}

	void Scene::BeginPlay() {
		for (auto& entity : Entities) {
			entity->BeginPlay();
		}
	}

	void Scene::Update(float deltaTime) {
		ScenePhysicsEngine->Simulate(Entities, deltaTime);

		for (auto entity : Entities) {
			entity->Tick(deltaTime);
		}
	}

	void Scene::Draw() const {
		SceneRenderer->Render(Entities);
	}
	
	Entity* Scene::SpawnEntity(const utils::Name& type, Entity* parent) {
		auto entity = utils::FactoryBase<Entity>::Create(type);
		if (!entity) {
			return nullptr;
		}

		Entities.push_back(entity);
		//entity->SetScene(this);
		entity->SetParent(parent);
		entity->Initialize();
		entity->BeginPlay();
		return entity;
	}

	void Scene::DestroyEntity(Entity* entity) {

	}
}