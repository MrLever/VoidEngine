#pragma once
//STD Headers
#include <initializer_list>

//Library Headers
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Void Engine Headers
#include "Shader.h"

namespace core {

	/**
	 * @class ShaderProgram
	 * @brief A ShaderProgram handles all the necessary operations to 
	 *        apply shaders during the rendering process
	 */
	class ShaderProgram {
	public:
		/**
		 * Constructor
		 * @param vertex The vertex shader this program will use
		 * @param fragment The fragment shader this program will use
		 */
		ShaderProgram(const std::string& name, Shader* vertex, Shader* fragment);

		/**
		 * Destructor
		 */
		~ShaderProgram();

		/**
		 * Instructs OpenGL to use this shader program for the next rendering
		 */
		void Use();

		/**
		 * Function to allow caller to set uniform values
		 * @param uniformName The name of the uniform to modify
		 * @param value The value to place in that uniform
		 */
		void SetUniform(const std::string& uniformName, float value);
		
		/**
		 * Function to allow caller to set uniform values
		 * @param uniformName The name of the uniform to modify
		 * @param value The value to place in that uniform
		 */
		void SetUniform(const std::string& uniformName, unsigned int value);

		/**
		 * Function to allow caller to set uniform values
		 * @param uniformName The name of the uniform to modify
		 * @param value The value to place in that uniform
		 */
		void SetUniform(const std::string& uniformName, int value);

		/**
		 * Function to allow caller to set uniform values
		 * @param uniformName The name of the uniform to modify
		 * @param value The value to place in that uniform
		 */
		void SetUniform(const std::string& uniformName, bool value);

		/**
		 * Function to allow caller to set uniform values
		 * @param uniformName The name of the uniform to modify
		 * @param value The value to place in that uniform
		 */
		void SetUniform(const std::string& uniformName, glm::mat4 value);

	private:
		/**
		 * Helper functions to allow the SetUniform functions to query uniform locations 
		 */
		GLint GetUniformLocation(const std::string& uniformName);

		/** Name used to identify this shader program */
		EngineUtils::Name ProgramName;

		/** Unique Identifier used by OpenGL to address this shader program */
		GLuint ProgramHandle;

		/** Flag to determine whether this shader program was properly linked */
		bool ProgramValid;
	};

}