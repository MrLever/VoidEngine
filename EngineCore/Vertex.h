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
		/** The vertex's position in model space */
		glm::vec3 Position;

		/** This vertex's normal vector */
		glm::vec3 Normal;

		/** This vertex's texture coordindate */
		glm::vec2 UV;
	};

}

