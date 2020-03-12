#pragma once
//STD Headers
#include <vector>

//Library Headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Void Engine Headers
#include "math/Vector.h"
#include "math/Rotator.h"

#include "core/gameplay_framework/Component.h"
#include "core/rendering/Model.h"

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
		
		/**
		 * Declare custom RTTI support
		 */
		TYPE_INFO_DECL(GraphicsComponent)

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
		 * Loads configuration data
		 */
		void Initialize() override;

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
		glm::mat4 m_TransformMatrix;

		/** The Shader Program to use when drawing this model */
		std::shared_ptr<ShaderProgram> m_Shader;

		/** This component's 3D model */
		std::shared_ptr<Model> m_Model;

		/** Whether this graphics component should be drawn */
		bool m_IsValid;

	};
}
