#pragma once
//STD Headers
#include <vector>

//Library Headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Void Engine Headers
#include "Component.h"
#include "Vector.h"
#include "Rotator.h"
#include "Model.h"

namespace core {
	//Forward class declarations
	class ShaderProgram;
	class Texture;

	/**
	 * @class GraphicsComponent
	 * @brief A graphics component represents all the data needed for the 
	 *        renderer to render an entity
	 */
	class GraphicsComponent : public Component {
		friend class Renderer;

	public:
		/**
		 * Constructor
		 * @param parent This component's parent
		 */
		GraphicsComponent(Entity* parent);

		/**
		 * Destructor
		 */
		~GraphicsComponent();

		/**
		 * Sets this component's 3D model
		 * @param verts The vertices of the 3D model
		 */
		void SetModel(std::shared_ptr<Model> model);

		/** 
		 * Assigns this component's 3D model a shader
		 * @param name The name of the material
		 * @param vertShaderPath The path to the material's vertex shader
		 * @param fragShaderPath The path to the materials fragment shader
		 */
		void AddMaterial(const std::string& name, const std::string& vertShaderPath, const std::string& fragShaderPath);

		/**
		 * Function to allow the renderer to draw this component
		 */
		void Draw() override;

	private:
		/** The this object's model matrix used for transformations in the vertex shader */
		glm::mat4 ModelMatrix;

		/** Vector of vertex data for the entity's model */
		std::vector<float> Vertices;

		/** The Shader Program to use when drawing this model */
		ShaderProgram* ComponentShader;

		/** This component's 3D model */
		std::shared_ptr<Model> ComponentModel;

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
