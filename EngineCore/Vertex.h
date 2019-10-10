#pragma once
//STD Headers

//Library Headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Void Engine Headers

namespace core {

	/**
	 * @struct Vertex
	 * @brief Structure used to represent vertex data for 3D models
	 */
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 UV;
	};

}

