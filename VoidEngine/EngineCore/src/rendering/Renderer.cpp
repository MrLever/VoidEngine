//STD Headers
#include <memory>

//Library Headers

//Void Engine Headers
#include "gameplay_framework/Entity.h"
#include "rendering/components/GraphicsComponent.h"
#include "rendering/Renderer.h"
#include "rendering/RenderCommand.h"
#include "Window.h"

namespace core {

	CameraComponent* Renderer::s_ActiveCamera = nullptr;

	glm::mat4 Renderer::s_DefualtViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -5));

	/** The default projection matrix to use if a scene does not provide one */
	glm::mat4 Renderer::s_DefaultProjectionMatrix = glm::perspective<float>(
		glm::radians(45.0f),
		(float)1280.0f / 720.0f,
		0.1f, 100.0f
	);

	Viewport Renderer::s_ActiveViewport;

	void Renderer::Initialize(Viewport viewport) {
		s_ActiveViewport = viewport;
		RenderCommand::Initialize();
		RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1});
	}

	void Renderer::HandleWindowResize(Viewport newViewport) {
		s_ActiveCamera->SetProjectionMatrix(newViewport);
		RenderCommand::SetViewport(newViewport);
	}

	void Renderer::BeginFrame(CameraComponent* activeCamera) {
		s_ActiveCamera = activeCamera;
		activeCamera->SetProjectionMatrix(s_ActiveViewport);

		RenderCommand::Clear();
	}

	void Renderer::EndFrame() {

	}

	void Renderer::Submit(
			std::shared_ptr<ShaderProgram> shader, 
			std::shared_ptr<VertexArray> vao, 
			const glm::mat4& model, 
			DrawMode drawMode
		) {

		shader->Use();
		shader->SetUniform("view", s_ActiveCamera->GetViewMatrix());
		shader->SetUniform("projection", s_ActiveCamera->GetProjectionMatrix());
		shader->SetUniform("model", model);

		vao->Bind();
		if (drawMode == DrawMode::TRIANGLE) {
			RenderCommand::DrawIndexed(vao);
		}
		else {
			RenderCommand::DrawWireframe(vao);
		}
	}

	RenderDevice::API Renderer::GetRendererAPI() {
		return RenderDevice::GetRendererAPI();
	}

}