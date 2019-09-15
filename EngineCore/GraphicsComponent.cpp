//STD Headers

//Library Headers

//Void Engine Headers
#include "GraphicsComponent.h"

namespace EngineCore {

	GraphicsComponent::GraphicsComponent(const std::vector<float>& model, const ShaderProgram& material)
	 : VAO(-1), IsValid(true), Vertices(std::move(model)), Material(std::move(material)) {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		//Initialize this component's VAO
		glBindVertexArray(VAO);

		//Bind VBO to VAO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices.data()), Vertices.data(), GL_STREAM_DRAW);

		//Set Vertex Attributes for VAO
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	GraphicsComponent::~GraphicsComponent() {
	}

	void GraphicsComponent::Draw() {	
		//Specify shader program
		Material.Use();

		//Activate VAO
		glBindVertexArray(VAO);

		//Draw component
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)Vertices.size());
	}

}