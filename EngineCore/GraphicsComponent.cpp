//STD Headers

//Library Headers

//Void Engine Headers
#include "GraphicsComponent.h"

#include "Entity.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "TimeUtils.h"

namespace EngineCore {
	glm::mat4 GraphicsComponent::ProjectionMatrix = glm::mat4(1);
	glm::mat4 GraphicsComponent::ViewMatrix = glm::mat4(1);

	GraphicsComponent::GraphicsComponent(Entity* parent)
	 : Component(parent), ModelMatrix(1.0f), VAO(-1), VBO(-1), EBO(-1), Material(nullptr), IsValid(true){

	}

	GraphicsComponent::~GraphicsComponent() {
		delete Material;
		for (auto &texture : Textures) {
			delete texture;
		}
	}

	void GraphicsComponent::SetModel(const std::vector<float>& verts) {
		Vertices = std::move(verts);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		//Initialize this component's VAO
		glBindVertexArray(VAO);

		//Bind VBO to VAO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Vertices.size(), Vertices.data(), GL_STATIC_DRAW);

		//Bind EBO to VAO
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//Set Vertex Attributes for VAO
		//Verticies
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		
		//Texture-coords
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void GraphicsComponent::AddMaterial(const std::string& name, const std::string& vertShaderPath, const std::string& fragShaderPath) {
		Material = new ShaderProgram(
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

	void GraphicsComponent::AddTexture(const std::string& name, const std::string& texturePath, GLint unit = 0) {
		auto texture = new Texture(name, texturePath, unit);
		texture->Load();
		texture->GenerateTextureInfo();

		if (Material) {
			Material->SetUniform(texture->GetName().c_str(), texture->GetUnit());
		}

		Textures.push_back(texture);
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
		if (Material) {
			Material->Use();
			Material->SetUniform("model", ModelMatrix);
			Material->SetUniform("view", ViewMatrix);
			Material->SetUniform("projection", ProjectionMatrix);
		}

		for (auto& texture : Textures) {
			texture->Use();
		}

		//Activate VAO
		glBindVertexArray(VAO);

		//Draw component
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)Vertices.size());
	}

}