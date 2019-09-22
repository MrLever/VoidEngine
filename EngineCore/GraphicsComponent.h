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
#include "Vector.h"
#include "Rotator.h"

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

		void SetPosition(const EngineMath::Vector3& position);

		void SetRotation(const EngineMath::Rotator& rotation);

		/**
		 * Sets this component's 3D model
		 * @param verts The vertices of the 3D model
		 */
		void SetModel(const std::vector<float>& verts);

		/** 
		 * Assigns this component's 3D model a shader
		 * @param name The name of the material
		 * @param vertShaderPath The path to the material's vertex shader
		 * @param fragShaderPath The path to the materials fragment shader
		 */
		void AddMaterial(const std::string& name, const std::string& vertShaderPath, const std::string& fragShaderPath);

		/**
		 * Adds a texture the the 3D model
		 * @param name The name of the texture
		 * @param texturePath A path to the texture's raw data
		 * @param unit The texture unit this texture fills
		 */
		void AddTexture(const std::string& name, const std::string& texturePath, GLint unit);

		/**
		 * Function to allow the renderer to draw this component
		 */
		void Draw();

	private:
		/** The position to be used for the translation of the model matrix in the next draw call */
		EngineMath::Vector3 Position;

		/** The rotation to be used when rotating the model matrix for drawing */
		EngineMath::Rotator Rotation;

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

		static glm::mat4 ViewMatrix;
		static glm::mat4 ProjectionMatrix;
	};
}
