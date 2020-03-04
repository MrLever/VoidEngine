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

	const LightingEnvironment* Renderer::s_LightingEnvironment = nullptr;

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
		RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
	}

	void Renderer::HandleWindowResize(Viewport newViewport) {
		s_ActiveCamera->SetProjectionMatrix(newViewport);
		RenderCommand::SetViewport(newViewport);
	}

	void Renderer::BeginFrame(CameraComponent* activeCamera, const LightingEnvironment* lighting) {
		s_ActiveCamera = activeCamera;
		s_LightingEnvironment = lighting;
		activeCamera->SetProjectionMatrix(s_ActiveViewport);

		RenderCommand::Clear();
	}

	void Renderer::EndFrame() {
		s_ActiveCamera = nullptr;
		s_LightingEnvironment = nullptr;
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
		shader->SetUniform("lightData.ambientStrength", s_LightingEnvironment->AmbientLightIntensity);
		shader->SetUniform("lightData.ambientColor", s_LightingEnvironment->AmbientLightColor);
		shader->SetUniform("viewPosition", s_ActiveCamera->GetPosition());

		ApplyDirectionalLightData(shader);
		ApplyPointLightData(shader);

		vao->Bind();
		if (drawMode == DrawMode::TRIANGLE) {
			RenderCommand::DrawIndexed(vao);
		}
		else {
			RenderCommand::DrawWireframe(vao);
		}
	}

	void Renderer::ApplyDirectionalLightData(std::shared_ptr<core::ShaderProgram>& shader)
	{
		int numDirLights = (int)s_LightingEnvironment->DirectionalLights.size();
		shader->SetUniform("lightData.numDirLights", numDirLights);

		if (numDirLights > MAX_DIR_LIGHTS) {
			utils::Logger::LogWarning("Too many directional lights in scene. Discarding excess");
			numDirLights = MAX_DIR_LIGHTS;
		}

		static const std::string structName("lightData");
		static const std::string variableName("directionalLights");
		for (int i = 0; i < numDirLights; i++) {
			std::string index("[" + std::to_string(i) + "]");
			shader->SetUniform(
				structName + "." + variableName + index + ".direction",
				s_LightingEnvironment->DirectionalLights[i]->GetDirection()
			);

			shader->SetUniform(
				structName + "." + variableName + index + ".color",
				s_LightingEnvironment->DirectionalLights[i]->GetColor()
			);

			shader->SetUniform(
				structName + "." + variableName + index + ".intensity",
				s_LightingEnvironment->DirectionalLights[i]->GetIntensity()
			);
		}
	}

	void Renderer::ApplyPointLightData(std::shared_ptr<core::ShaderProgram>& shader) {
		int numPtLights = (int)s_LightingEnvironment->PointLights.size();
		shader->SetUniform("lightData.numPtLights", numPtLights);

		if (numPtLights > MAX_PT_LIGHTS) {
			utils::Logger::LogWarning("Too many point lights in scene. Discarding excess");
			numPtLights = MAX_PT_LIGHTS;
		}

		static const std::string structName("lightData");
		static const std::string variableName("pointLights");
		for (int i = 0; i < numPtLights; i++) {
			std::string index("[" + std::to_string(i) + "]");
			auto var = structName + "." + variableName + index + ".position";
			shader->SetUniform(
				structName + "." + variableName + index + ".position",
				s_LightingEnvironment->PointLights[i]->GetPosition()
			);

			shader->SetUniform(
				structName + "." + variableName + index + ".color",
				s_LightingEnvironment->PointLights[i]->GetColor()
			);

			shader->SetUniform(
				structName + "." + variableName + index + ".intensity",
				s_LightingEnvironment->PointLights[i]->GetIntensity()
			);
		}
	}
	
	RenderDevice::API Renderer::GetRendererAPI() {
		return RenderDevice::GetRendererAPI();
	}

}