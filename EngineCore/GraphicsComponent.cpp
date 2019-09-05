//STD Headers

//Library Headers


//Void Engine Headers
#include "GraphicsComponent.h"

namespace EngineCore {

	GraphicsComponent::GraphicsComponent(const std::vector<float>& model, const ShaderProgram& material)
	 : VAO(-1), IsValid(true), Vertices(std::move(model)), Material(std::move(material)) {
		glGenBuffers(1, &VBO);
	}

	GraphicsComponent::~GraphicsComponent() {
	}

}