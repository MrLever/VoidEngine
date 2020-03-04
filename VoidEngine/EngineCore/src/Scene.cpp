//STD Headers

//Library Headers

//Void Engine Headers
#include "Scene.h"
#include "rendering/components/lights/PointLightComponent.h"
#include "rendering/components/lights/PointLightComponent.h"

namespace core {
	Scene::Scene(
		EventBus* eventBus, 
		std::shared_ptr<InputManager> inputManager,
		std::shared_ptr<PhysicsEngine> physicsEngine) 
		: EventBusNode(eventBus), m_InputManager(inputManager), m_PhysicsEngine(physicsEngine), m_ActiveCamera(nullptr) {

	}

	Scene::~Scene() {
		for (auto& entity : m_Entities) {
			delete entity;
			entity = nullptr;
		}
	}
	
	void Scene::ReceiveEvent(Event* event) {
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowResizedEvent>(
			[this](WindowResizedEvent* event) {
				Renderer::HandleWindowResize({0,0, event->GetWidth(), event->GetHeight()});
			}
		);
	}

	void Scene::AddCamera(CameraComponent* camera) {
		m_Cameras.insert({camera->GetName(), camera});
		ActivateCamera(camera->GetName());
	}

	void Scene::RemoveCamera(CameraComponent* camera) {
		m_Cameras.erase(camera->GetName());
	}

	void Scene::ActivateCamera(utils::Name cameraName) {
		if (m_Cameras.find(cameraName) == m_Cameras.end()) {
			utils::Logger::LogError("Camera " + cameraName.StringID + " not found. Camara not activated");
			return;
		}

		m_ActiveCamera = m_Cameras[cameraName];
	}

	void Scene::BeginPlay() {
		for (auto& entity : m_Entities) {
			auto camera = entity->GetComponent<CameraComponent>();
			if (camera) {
				AddCamera(camera);
			}
			entity->BeginPlay();
		}
	}

	void Scene::ProcessInput(float deltaTime) {
		m_InputManager->ProcessInput(m_Entities, deltaTime);
	}

	void Scene::Update(float deltaTime) {
		m_PhysicsEngine->Simulate(m_Entities, deltaTime);

		for (auto entity : m_Entities) {
			entity->Tick(deltaTime);
		}

		for (auto entity : m_SpawnQueue) {
			m_Entities.push_back(entity);
			entity->Initialize();
			entity->BeginPlay();
		}
		m_SpawnQueue.clear();
	}

	void Scene::Draw() {
		GatherLights();
		Renderer::BeginFrame(m_ActiveCamera, &m_LightingEnvironment);
		
		for (auto entity : m_Entities) {
			entity->Draw();
		}
		
		Renderer::EndFrame();
	}
	
	Entity* Scene::SpawnEntity(const utils::Name& type, Entity* parent) {
		auto entity = utils::FactoryBase<Entity>::Create(type);
		if (!entity) {
			return nullptr;
		}

		m_SpawnQueue.push_back(entity);
		entity->SetScene(this);
		entity->SetParent(parent);
		return entity;
	}

	void Scene::DestroyEntity(Entity* entity) {

	}
	
	std::string Scene::GetControlFilePath() const {
		return m_ControlFilePath;
	}

	void Scene::GatherLights() {
		//Reset light data
		m_LightingEnvironment.DirectionalLights = {};
		m_LightingEnvironment.PointLights = {};

		//Gather all lights in scene
		for (const auto& entity : m_Entities) {
			auto dirLight = entity->GetComponent<DirectionalLightComponent>();
			if (dirLight) {
				m_LightingEnvironment.DirectionalLights.push_back(dirLight);
			}

			auto ptLight = entity->GetComponent<PointLightComponent>();
			if (ptLight) {
				m_LightingEnvironment.PointLights.push_back(ptLight);
			}
		}
	}
}