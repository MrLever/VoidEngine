#pragma once
//STD Headers

//Library Headers
#include "glad/glad.h"

//Void Engine Headers

namespace EngineCore {

	/**
	 * @class ShaderProgram
	 * @brief A ShaderProgram handles all the necessary operations to 
	 *        apply shaders during the rendering process
	 */
	class ShaderProgram {
	public:

	private:
		/** Unique Identifier used by OpenGL to address this shader program */
		GLuint ProgramID;
	};

}