#pragma once
//STD Header
#include <string>

//Library Headers
#include "glad/glad.h"

//Void Engine Headers
#include "Resource.h"
#include "Name.h"

namespace EngineCore {

	enum class ShaderType {
		VERTEX = GL_VERTEX_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER,
		COMPUTE = GL_COMPUTE_SHADER
	};
	class Shader : public EngineUtils::Resource {
		friend class ShaderProgram;

	public:
		/**
		 * Constructor 
		 * @param name The shader's name
		 * @param filePath Location of the shader source code
		 */
		Shader(const std::string& name, ShaderType type, const std::string& filePath);

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


	private:
		
		/**
		 * Compiles shader code
		 * @return Whether that compilation was successful
		 */
		bool Compile();
		
		EngineUtils::Name ShaderName;

		ShaderType Type;

		std::string ShaderSource;

		GLuint ShaderHandle;
	};

}