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
		: EventBusNode(eventBus), m_InputManager(inputManager), m_PhysicsEngine(physicsEngine), m_ActiveCamera(nullptr) {

		auto levelData = s_LevelCache.GetResource(levelPath);

		m_ControlFilePath = levelData->GetAttribute<std::string>("controlFile");
		m_PhysicsEngine->SetGravity(levelData->GetAttribute<float>("gravity"));

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

			entity->Initialize();
			m_Entities.emplace_back(std::move(entity));
		}

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
		for (auto it = m_Cameras.begin(); it != m_Cameras.end(); it++) {
			if (*it = camera) {
				m_Cameras.erase(it);
				break;
			}
		}
	}

	void Scene::ActivateCamera(CameraComponent* camera) {
		m_ActiveCamera = camera;
	}

	void Scene::BeginPlay() {
		m_Cameras = FindComponentsOfType<CameraComponent>();
		if (m_Cameras.size() > 0 && m_Cameras[0]) {
			ActivateCamera(m_Cameras[0]);
		}

		for (auto& entity : m_Entities) {	
			entity->BeginPlay();
		}
	}

	void Scene::ProcessInput(float deltaTime) {
		m_InputManager->ProcessInput(m_Entities, deltaTime);
	}

	void Scene::Update(float deltaTime) {
		m_PhysicsEngine->Simulate(m_Entities, deltaTime);

		for (auto& entity : m_Entities) {
			entity->Tick(deltaTime);
		}
	}

	void Scene::Draw() {
		m_LightingEnvironment.DirectionalLights = FindComponentsOfType<DirectionalLightComponent>();
		m_LightingEnvironment.PointLights = FindComponentsOfType<PointLightComponent>();
		Renderer::BeginFrame(m_ActiveCamera, &m_LightingEnvironment);
		
		for (auto& entity : m_Entities) {
			entity->Draw();
		}
		
		Renderer::EndFrame();
	}
	
	Entity* Scene::Instantiate(const Prototype& prototype, Entity* parent) {
		Entity* entity = SpawnEntity(prototype.GetData()).get();
		entity->Initialize();

		return entity;
	}

	void Scene::DestroyEntity(Entity* entity) {

	}
	
	std::string Scene::GetControlFilePath() const {
		return m_ControlFilePath;
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