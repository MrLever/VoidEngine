#pragma once
//STD Headers
#include <vector>

//Library Headers
#include <glad/glad.h>

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

		void SetModel(const std::vector<float>& verts);

		void AddMaterial(const std::string& name, const std::string& vertShaderPath, const std::string& fragShaderPath);

		void AddTexture(const std::string& texturePath);

	private:
		/**
		 * Function to allow the renderer to draw this component
		 */
		void Draw();

		/** Vector of vertex data for the entity's model */
		std::vector<float> Vertices;

		/** The Shader Program to use when drawing this model */
		ShaderProgram* Material;

		/** The texture to be used when drawing this component */
		Texture* Tex;

		/** Whether this graphics component should be drawn */
		bool IsValid;

		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
	};
}
