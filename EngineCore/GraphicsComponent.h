#pragma once
//STD Headers
#include <vector>

//Library Headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Void Engine Headers
#include "ShaderProgram.h"
#include "Texture.h"

namespace EngineCore {
	/**
	 * @class GraphicsComponent
	 * @brief A graphics component represents all the data needed for the 
	 *        renderer to render an entity
	 */
	class GraphicsComponent {
		friend class Renderer;

	public:
		/**
		 * Constructor
		 */
		GraphicsComponent();

		/**
		 * Destructor
		 */
		~GraphicsComponent();

		/**
		 * Sets this component's 3D model
		 */
		void SetModel(const std::vector<float>& verts);

		/** 
		 * Assigns this component's 3D model a shader
		 */
		void AddMaterial(const std::string& name, const std::string& vertShaderPath, const std::string& fragShaderPath);

		/**
		 * Adds a texture the the 3D model
		 */
		void AddTexture(const std::string& name, const std::string& texturePath, GLint unit);

	private:
		/**
		 * Function to allow the renderer to draw this component
		 */
		void Draw(glm::mat4 view, glm::mat4 projection);

		/** The this object's model matrix used for transformations in the vertex shader */
		glm::mat4 ModelMatrix;

		/** Vector of vertex data for the entity's model */
		std::vector<float> Vertices;

		/** The Shader Program to use when drawing this model */
		ShaderProgram* Material;

		/** The set of textures this onject uses when drawn */
		std::vector<Texture*> Textures;

		/** Whether this graphics component should be drawn */
		bool IsValid;

		/** The Vertex Array Object used to draw this component */
		GLuint VAO;

		/** The Vertex Buffer Object used to draw this component */
		GLuint VBO;

		/** The Element Buffer Object used to draw this component */
		GLuint EBO;
	};
}
