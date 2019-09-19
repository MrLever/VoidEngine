//STD Headers

//Library Headers

//Void Engine Headers
#include "GraphicsComponent.h"
#include "TimeUtils.h"

namespace EngineCore {

	GraphicsComponent::GraphicsComponent()
	 : VAO(-1), VBO(-1), EBO(-1), Material(nullptr), IsValid(true){

	}

	GraphicsComponent::~GraphicsComponent() {
		delete Material;
	}

	void GraphicsComponent::SetModel(const std::vector<float>& verts) {
		Vertices = std::move(verts);
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		//Initialize this component's VAO
		glBindVertexArray(VAO);

		//Bind VBO to VAO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Vertices.size(), Vertices.data(), GL_STATIC_DRAW);

		//Bind EBO to VAO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

	void GraphicsComponent::AddTexture(const std::string& texturePath) {
		CurrTexture = new Texture(texturePath);
		CurrTexture->Load();
		CurrTexture->GenerateTextureInfo();
	}

	void GraphicsComponent::Draw() {	
		static float col = 0;
		Material->SetUniform("desiredColor", std::sin(col++) / 2 + .5f);
		
		//Specify shader program
		if (Material) {
			Material->Use();
		}

		if (CurrTexture) {
			CurrTexture->Use();
		}

		//Activate VAO
		glBindVertexArray(VAO);

		//Draw component
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

}