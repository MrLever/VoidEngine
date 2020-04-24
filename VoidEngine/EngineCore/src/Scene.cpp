//STD Headers

//Library Headers

//Void Engine Headers
#include "Scene.h"
#include "rendering/components/lights/PointLightComponent.h"
#include "rendering/components/lights/DirectionalLightComponent.h"

namespace core {
	utils::ResourceAllocator<utils::JsonResource> Scene::s_LevelCache;

	Scene::Scene(
		const std::string& levelPath,
		EventBus* eventBus, 
		std::shared_ptr<InputManager> inputManager,
		std::shared_ptr<PhysicsEngine> physicsEngine) 
		: EventBusNode(eventBus), reset(false), inputManager(inputManager), physicsEngine(physicsEngine), activeCamera(nullptr) {
		
		levelData = s_LevelCache.GetResource(levelPath);
		SpawnInitialScene();

	}

	Scene::~Scene() {

	}
	
	void Scene::ReceiveEvent(Event* event) {
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowResizedEvent>(
			[this](WindowResizedEvent* event) {
				Renderer::HandleWindowResize({0,0, event->GetWidth(), event->GetHeight()});
			}
		);
	}

	void Scene::RemoveCamera(CameraComponent* camera) {
		for (auto it = cameras.begin(); it != cameras.end(); it++) {
			if (*it = camera) {
				cameras.erase(it);
				break;
			}
		}
	}

	void Scene::ActivateCamera(CameraComponent* camera) {
		activeCamera = camera;
	}

	void Scene::BeginPlay() {
		cameras = FindComponentsOfType<CameraComponent>();
		if (cameras.size() > 0 && cameras[0]) {
			ActivateCamera(cameras[0]);
		}

		for (auto& entity : entities) {	
			entity->BeginPlay();
		}
	}

	void Scene::ProcessInput(float deltaTime) {
		inputManager->ProcessInput(entities, deltaTime);
	}

	void Scene::Update(float deltaTime) {
		physicsEngine->Simulate(entities, deltaTime);

		for (auto& entity : entities) {
			entity->Tick(deltaTime);
		}

		ProcessSpawnQueue();
		ProcessDestructionQueue();

		if (reset) {
			entities.clear();
			SpawnInitialScene();
			BeginPlay();
			reset = false;
		}
	}

	void Scene::Draw() {
		m_LightingEnvironment.DirectionalLights = FindComponentsOfType<DirectionalLightComponent>();
		m_LightingEnvironment.PointLights = FindComponentsOfType<PointLightComponent>();
		m_LightingEnvironment.SpotLights = FindComponentsOfType<SpotlightComponent>();
		Renderer::BeginFrame(activeCamera, &m_LightingEnvironment);
		
		for (auto& entity : entities) {
			entity->Draw();
		}
		
		Renderer::EndFrame();
	}

	void Scene::RestartLevel() {
		reset = true;
	}

	Entity* Scene::SpawnEntity(const Prototype& prototype, Entity* parent) {
		auto entity = SpawnEntity(prototype.GetData());
		auto weakPtr = entity.get();

		entity->Initialize();
		spawnQueue.push_back({ std::move(entity), parent });

		return weakPtr;
	}
	
	Entity* Scene::SpawnEntity(const Prototype& prototype, const Transform& transform, Entity* parent) {
		auto entity = SpawnEntity(prototype.GetData());
		auto weakPtr = entity.get();

		entity->Initialize();
		entity->transform = transform;
		spawnQueue.push_back({ std::move(entity), parent });

		return weakPtr;
	}

	void Scene::Reparent(Entity* child, Entity* parent) {
		for (auto it = entities.begin(); it != entities.end(); it++) {
			if (it->get() == child) {
				auto handle = std::move(*it);
				entities.erase(it);

				parent->AddChild(std::move(handle));
				return;
			}
		}
	}

	void Scene::Destroy(Entity* entity) {
		destructionQueue.insert(entity);
	}
	
	std::string Scene::GetControlFilePath() const {
		return controlFilePath;
	}

	Entity* Scene::FindEntityByID(unsigned ID) {
		for (auto& entity : entities) {
			if (entity->GetID() == ID) {
				return entity.get();
			}
		}

		return nullptr;
	}

	void Scene::SpawnInitialScene() {
		controlFilePath = levelData->GetAttribute<std::string>("controlFile");
		physicsEngine->SetGravity(levelData->GetAttribute<float>("gravity"));

		auto lightSettings = levelData->GetAttribute<nlohmann::json>("lightSettings");

		//Gather scene's ambient light data
		m_LightingEnvironment.AmbientLightColor = math::Vector4(
			lightSettings["ambientLightColor"][0],
			lightSettings["ambientLightColor"][1],
			lightSettings["ambientLightColor"][2],
			lightSettings["ambientLightColor"][3]
			);

		m_LightingEnvironment.AmbientLightIntensity = lightSettings["ambientLightIntensity"];

		auto entityList = levelData->GetAttribute<nlohmann::json>("entities");

		for (auto& entityData : entityList) {
			auto entity = SpawnEntity(entityData);

			if (entity == nullptr) continue;

			entities.emplace_back(std::move(entity));
		}

		for (auto& entity : entities) {
			entity->Initialize();
		}
	}

	void Scene::ProcessSpawnQueue() {
		//Process the spawn queue
		for (auto& entry : spawnQueue) {
			auto parent = entry.second;
			std::unique_ptr<Entity> entity(std::move(entry.first));
			entity->BeginPlay();

			if (parent == nullptr) {
				entities.emplace_back(std::move(entity));
			}
			else {
				parent->AddChild(std::move(entity));
			}
		}

		//Clear the processed queue
		spawnQueue.clear();
	}

	void Scene::ProcessDestructionQueue() {

		if (destructionQueue.size() == 0) {
			return;
		}

		auto predicate = [this](std::unique_ptr<Entity>& entityHandle) {
			auto entity = entityHandle.get();

			if (destructionQueue.find(entity) != destructionQueue.end()) {
				destructionQueue.erase(entity);
				entity->OnDestroy();
				return true;
			}
			else {
				entity->DestroyFromChildren(destructionQueue);
				return false;
			}
		};

		entities.erase(
			std::remove_if(entities.begin(), entities.end(), predicate),
			entities.end()
		);

		destructionQueue.clear();
	}

	std::unique_ptr<Entity> Scene::SpawnEntity(const nlohmann::json& entityData) {
		auto entityType = entityData["type"].get<std::string>();
		
		std::unique_ptr<Entity> entity(
			utils::FactoryBase<Entity>::Create(entityType)
		);

		entity->SetConfigData(entityData);
		entity->SetScene(this);

		if (entityData.find("components") != entityData.end()) {
			auto componentList = entityData["components"];

			for (auto componentEntry : componentList) {
				auto componentType = componentEntry["type"].get<std::string>();

				std::shared_ptr<Component> component(utils::FactoryBase<Component>::Create(componentType));

				if (component) {
					entity->AddComponent(component);
					component->SetConfigData(componentEntry);
				}
			}
		}

		//Recursively load child enitites
		if (entityData.find("children") != entityData.end()) {
			auto childrenData = entityData["children"];
			for (auto& childData : childrenData) {
				auto child = SpawnEntity(childData);
				
				if (child.get() == nullptr) continue;

				entity->AddChild(std::move(child));
			}
		}

		return entity;
	}

}