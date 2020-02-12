//STD Headers
#include <memory>

//Library Headers

//Void Engine Headers
#include "gameplay_framework/Entity.h"
#include "rendering/components/GraphicsComponent.h"
#include "rendering/Renderer.h"
#include "Window.h"

namespace core {

	Renderer::Renderer(
			EventBus* bus,
			std::shared_ptr<RenderingContext> renderingAPI,
			const utils::ResourceHandle<utils::Configuration>& configuration
		) : Configurable(configuration), 
			EventBusNode(bus), 
			RenderingAPI(std::move(renderingAPI)) {
	
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

	void Renderer::Render(Level* scene) {
		//Set the view and projection matrices for all graphics components for this draw call 
		auto activeCamera = Window::GetActiveWindow()->GetView();
		if (activeCamera == nullptr) {
			GraphicsComponent::ViewMatrix = DefualtViewMatrix;
			GraphicsComponent::ProjectionMatrix = DefaultProjectionMatrix;
		}
		else {
			GraphicsComponent::ViewMatrix = activeCamera->GetViewMatrix();
			GraphicsComponent::ProjectionMatrix = activeCamera->GetProjectionMatrix();
		}

		auto entities = scene->GetScene();

		//Clear the color and depth buffer
		RenderingAPI->Clear();

		//Draw entities
		for (const auto& entity : entities) {
			entity->Draw();
		}
	}

	void Renderer::Configure() {
		//TODO (MrLever): Leverage configuration settings
	}

	void Renderer::HandleWindowResize(WindowResizedEvent* event) {
		auto activeCamera = Window::GetActiveWindow()->GetView();
		
		auto viewport = RenderingAPI->GetViewport();

		activeCamera->UpdateProjectionMatrix(viewport);

		DefaultProjectionMatrix = glm::perspective<float>(
			glm::radians(45.0f),
			(float) viewport.Width / viewport.Height,
			0.1f, 100.0f
		);
	}

}