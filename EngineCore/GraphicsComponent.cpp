//STD Headers

//Library Headers


//Void Engine Headers
#include "GraphicsComponent.h"

namespace EngineCore {

	GraphicsComponent::GraphicsComponent() : VAO(-1), VBO(-1), IsValid(false) {
	}

	GraphicsComponent::GraphicsComponent(const std::vector<float>& verts) 
		: VAO(-1), VBO(-1), IsValid(true), Vertices(std::move(verts)) {
		glGenBuffers(1, &VBO);
	}

	GraphicsComponent::~GraphicsComponent() {
	}

}