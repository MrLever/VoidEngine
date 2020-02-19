//STD Headers
#include <memory>

//Library Headers

//Void Engine Headers
#include "gameplay_framework/Entity.h"
#include "rendering/components/GraphicsComponent.h"
#include "rendering/Renderer.h"
#include "Window.h"

namespace core {

	Renderer::Renderer(EventBus* bus, std::shared_ptr<RenderingContext> renderingAPI) 
		: EventBusNode(bus), RenderingAPI(std::move(renderingAPI)) {
	
		//Set default view matrix
		DefualtViewMatrix = glm::mat4(1.0f);
		DefualtViewMatrix = glm::translate(DefualtViewMatrix, glm::vec3(0, 0, -5));
		
		auto viewport = RenderingAPI->GetViewport();

		//Set default projection matrix
		DefaultProjectionMatrix = glm::perspective<float>(
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

	void Renderer::Render(std::vector<Entity*> entities) {
		if (ActiveCamera == nullptr) {
			GraphicsComponent::ViewMatrix = DefualtViewMatrix;
			GraphicsComponent::ProjectionMatrix = DefaultProjectionMatrix;
		}
		else {
			GraphicsComponent::ViewMatrix = ActiveCamera->GetViewMatrix();
			GraphicsComponent::ProjectionMatrix = ActiveCamera->GetProjectionMatrix();
		}

		//Clear the color and depth buffer
		RenderingAPI->Clear();

		//Draw entities
		for (const auto& entity : entities) {
			entity->Draw();
		}
	}

	void Renderer::InitializeCamera(CameraComponent* camera) const {
		camera->UpdateProjectionMatrix(RenderingAPI->GetViewport());
	}

	void Renderer::UseCamera(CameraComponent* camera) {
		ActiveCamera = camera;
	}

	void Renderer::HandleWindowResize(WindowResizedEvent* event) {
		auto viewport = RenderingAPI->GetViewport();

		ActiveCamera->UpdateProjectionMatrix(viewport);

		DefaultProjectionMatrix = glm::perspective<float>(
			glm::radians(45.0f),
			(float) viewport.Width / viewport.Height,
			0.1f, 100.0f
		);
	}

}