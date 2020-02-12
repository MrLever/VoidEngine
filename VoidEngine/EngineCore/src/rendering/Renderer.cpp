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
		
		ContextWidth = GameWindow->GetWindowWidth();
		ContexHeight = GameWindow->GetWindowHeight();

		//Set default view matrix
		DefualtViewMatrix = glm::mat4(1.0f);
		DefualtViewMatrix = glm::translate(DefualtViewMatrix, glm::vec3(0, 0, -5));
		
		//Set default projection matrix
		DefaultProjectionMatrix = glm::perspective<float>(
			glm::radians(45.0f),
			(float)ContextWidth / ContexHeight,
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

		auto windowWidth = GameWindow->GetWindowWidth();
		auto windowHeight = GameWindow->GetWindowHeight();

		auto entities = scene->GetScene();

		//Clear the color and depth buffer
		glClearColor(0.24f, 0.28f, 0.28f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Draw entities
		for (const auto& entity : entities) {
			entity->Draw();
		}

		GameWindow->SwapBuffers();
	}

	void Renderer::Configure() {
		//TODO (MrLever): Leverage configuration settings
	}

	void Renderer::HandleWindowResize(WindowResizedEvent* event) {
		ContextWidth = event->GetWidth();
		ContexHeight = event->GetHeight();

		auto activeCamera = Window::GetActiveWindow()->GetView();
		activeCamera->UpdateProjectionMatrix();

		DefaultProjectionMatrix = glm::perspective<float>(
			glm::radians(45.0f),
			(float)ContextWidth / ContexHeight,
			0.1f, 100.0f
		);
	}

}