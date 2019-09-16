#pragma once
//STD Headers
#include <initializer_list>

//Library Headers
#include "glad/glad.h"

//Void Engine Headers
#include "Shader.h"

namespace EngineCore {

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
		ShaderProgram(const std::string& name, Shader& vertex, Shader& fragment);

		/**
		 * Destructor
		 */
		~ShaderProgram();

		/**
		 * Instructs OpenGL to use this shader program for the next rendering
		 */
		void Use();

	private:
		/** Name used to identify this shader program */
		EngineUtils::Name ProgramName;

		/** Unique Identifier used by OpenGL to address this shader program */
		GLuint ProgramHandle;

		/** Flag to determine whether this shader program was properly linked */
		bool ProgramValid;
	};

}