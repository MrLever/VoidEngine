//STD Headers

//Library Headers

//Void Engine Headers
#include "GraphicsComponent.h"

#include "Entity.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "TimeUtils.h"

namespace core {
	glm::mat4 GraphicsComponent::ProjectionMatrix = glm::mat4(1);
	glm::mat4 GraphicsComponent::ViewMatrix = glm::mat4(1);

	GraphicsComponent::GraphicsComponent(Entity* parent)
	 : Component(parent), ModelMatrix(1.0f), VAO(-1), VBO(-1), EBO(-1), ComponentShader(nullptr), IsValid(true){

	}

	GraphicsComponent::~GraphicsComponent() {
		delete ComponentShader;
	}

	void GraphicsComponent::SetModel(std::shared_ptr<Model> model) {

	}

	void GraphicsComponent::AddMaterial(const std::string& name, const std::string& vertShaderPath, const std::string& fragShaderPath) {
		ComponentShader = new ShaderProgram(
			name,
			new Shader(
				ShaderType::VERTEX,
				vertShaderPath
			),
			new Shader(
				ShaderType::FRAGMENT,
				fragShaderPath
			)
		);
	}

	void GraphicsComponent::Draw() {
		Position = Parent->GetPostion();
		Rotation = Parent->GetRotation();

		ModelMatrix = glm::mat4(1.0f);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(Position.X, Position.Y, Position.Z));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.Roll), glm::vec3(0.0f, 0.0f, 1.0f));

		//Specify shader program
		if (ComponentShader) {
			ComponentShader->Use();
			ComponentShader->SetUniform("model", ModelMatrix);
			ComponentShader->SetUniform("view", ViewMatrix);
			ComponentShader->SetUniform("projection", ProjectionMatrix);
		}

		ComponentModel->Draw(ComponentShader);
	}

}