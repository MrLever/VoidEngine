//STD Headers
#include <memory>

//Library Headers

//Void Engine Headers
#include "gameplay_framework/Entity.h"
#include "rendering/components/GraphicsComponent.h"
#include "rendering/Renderer.h"
#include "Window.h"

namespace core {

	Renderer::Renderer(EventBus* bus, std::shared_ptr<RenderDevice> renderingAPI) 
		: EventBusNode(bus), ActiveCamera(nullptr), m_RenderingAPI(std::move(renderingAPI)) {
	
		//Set default view matrix
		m_DefualtViewMatrix = glm::mat4(1.0f);
		m_DefualtViewMatrix = glm::translate(m_DefualtViewMatrix, glm::vec3(0, 0, -5));
		
		auto viewport = m_RenderingAPI->GetViewport();
		m_RenderingAPI->SetClearColor(math::Vector4(0.2f, 0.2f, 0.2f, 0.2f));

		//Set default projection matrix
		m_DefaultProjectionMatrix = glm::perspective<float>(
			glm::radians(45.0f),
			(float)viewport.Width / viewport.Height,
			0.1f, 100.0f
		);
	}

	Renderer::~Renderer() {

	}

	void Renderer::ReceiveEvent(Event* event) {
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowResizedEvent>(
			[this](WindowResizedEvent* event) {
				HandleWindowResize(event);
			}
		);
	}

	unsigned Renderer::GetSubscription() {
		return static_cast<unsigned>(EventCategory::WINDOW);
	}

	void Renderer::InitializeEnvironment(Scene* scene) {

	}

	void Renderer::ClearEnvironment() {

	}

	void Renderer::Submit(GraphicsComponent* drawData) {

	}

	void Renderer::Render(std::vector<Entity*> entities) {
		if (ActiveCamera == nullptr) {
			GraphicsComponent::ViewMatrix = m_DefualtViewMatrix;
			GraphicsComponent::ProjectionMatrix = m_DefaultProjectionMatrix;
		}
		else {
			GraphicsComponent::ViewMatrix = ActiveCamera->GetViewMatrix();
			GraphicsComponent::ProjectionMatrix = ActiveCamera->GetProjectionMatrix();
		}

		//Clear the color and depth buffer
		m_RenderingAPI->Clear();

		//Draw entities
		for (const auto& entity : entities) {
			entity->Draw();
		}
	}

	void Renderer::InitializeCamera(CameraComponent* camera) const {
		camera->UpdateProjectionMatrix(m_RenderingAPI->GetViewport());
	}

	void Renderer::UseCamera(CameraComponent* camera) {
		ActiveCamera = camera;
	}

	RenderDevice::API Renderer::GetRendererAPI() {
		return RenderDevice::GetRendererAPI();
	}

	void Renderer::HandleWindowResize(WindowResizedEvent* event) {
		auto viewport = m_RenderingAPI->GetViewport();

		ActiveCamera->UpdateProjectionMatrix(viewport);

		m_DefaultProjectionMatrix = glm::perspective<float>(
			glm::radians(45.0f),
			(float) viewport.Width / viewport.Height,
			0.1f, 100.0f
		);
	}

}