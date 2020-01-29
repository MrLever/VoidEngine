#pragma once
//STD Header
#include <string>

//Library Headers
#include "glad/glad.h"

//Void Engine Headers
#include "utils/Name.h"
#include "utils/resource/Resource.h"

namespace core {

	enum class ShaderType {
		VERTEX = GL_VERTEX_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER,
		COMPUTE = GL_COMPUTE_SHADER
	};
	class Shader : public utils::Resource {
		friend class ShaderProgram;

	public:
		/**
		 * Constructor 
		 * @param name The shader's name
		 * @param filePath Location of the shader source code
		 */
		Shader(ShaderType type, const std::string& filePath);

		/**
		 * Destructor
		 */
		~Shader();

		/**
		 * Loads a given resource from main memory
		 */
		bool Load() override;

		/**
		 * Loads the resource's defualt value if the path provided is invalid
		 */
		bool LoadErrorResource() override;

		/**
		 * Compiles shader code
		 */
		virtual void Initialize();


	private:
		/**
		 * Enumeration value that specifies what type of shader this is
		 */
		ShaderType Type;

		/**
		 * The shader's source code
		 */
		std::string ShaderSource;

		/**
		 * OpenGL object used to address this shader
		 */
		GLuint ShaderHandle;
	};

}