#pragma once
//STD Headers
#include <vector>

//Library Headers
#include <glad/glad.h>

//Void Engine Headers
#include "ShaderProgram.h"

namespace EngineCore {
	/**
	 * @class GraphicsComponent
	 * @brief A graphics component represents all the data needed for the 
	 *        renderer to render an entity
	 */
	class GraphicsComponent	{
		friend class Renderer;
	
	public:
		/**
		 * Constructor
		 * @param model The model's vertices
		 * @param material The model's shader
		 */
		GraphicsComponent(const std::vector<float>& model, const ShaderProgram& material);

		/**
		 * Destructor
		 */
		~GraphicsComponent();


	private:
		/**
		 * Function to allow the renderer to draw this component
		 */
		void Draw();
		
		/** Vector of vertex data for the entity's model */
		std::vector<float> Vertices;

		/** The Shader Program to use when drawing this model */
		ShaderProgram Material;

		/** Whether this graphics component should be drawn */
		bool IsValid;

		GLuint VAO;
		GLuint VBO;
	};
}
