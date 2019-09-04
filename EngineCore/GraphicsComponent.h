#pragma once
//STD Headers
#include <vector>

//Library Headers
#include <glad/glad.h>

//Void Engine Headers

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
		 */
		GraphicsComponent();

		/**
		 * Constructor
		 * @param verts The model's vertices
		 */
		GraphicsComponent(const std::vector<float>& verts);

		/**
		 * Destructor
		 */
		~GraphicsComponent();

		/** Vector of vertex data for the entity's model */
		std::vector<float> Vertices;

		/** Whether this graphics component should be drawn */
		bool IsValid;

		GLuint VAO;
		GLuint VBO;
	};
}
