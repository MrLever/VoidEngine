//STD Headers
#include <memory>

//Library Headers

//Void Engine Headers
#include "Entity.h"
#include "GraphicsComponent.h"
#include "Renderer.h"
#include "Window.h"

namespace core {

	Renderer::Renderer(
			EventBus* bus,
			std::shared_ptr<Window> window,
			const utils::ResourceHandle<utils::Configuration>& configuration
		) : Configurable(configuration), EventBusNode(bus), GameWindow(std::move(window)) {
		
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLDebugCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		
		//Enable Depth Buffer
		glEnable(GL_DEPTH_TEST);

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

	void OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		// ignore non-significant error/warning codes
		if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

		std::cout << "---------------\n";
		std::cout << "OpenGL Debug message (" << id << "): " << message << "\n";

		switch (source) {
		case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
		case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
		case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
		} 
		std::cout << "\n";

		switch (type) {
		case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
		case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
		case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
		case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
		case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
		case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
		} 
		std::cout << "\n";

		switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
		case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
		case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
		} 
		std::cout << "\n";
		std::cout << std::endl;
	}

}