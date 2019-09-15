//STD Headers

//Library Headers

//Void Engine Headers
#include "ShaderProgram.h"

namespace EngineCore {

	ShaderProgram::ShaderProgram(const std::string& name, Shader& vertex, Shader& fragment) 
		: ProgramName(std::move(name)) {

		bool vertexValid = vertex.Compile();
		bool fragmentValid = fragment.Compile();

		if (vertexValid && fragmentValid) {

			ProgramHandle = glCreateProgram();
			glAttachShader(ProgramHandle, vertex.ShaderHandle);
			glAttachShader(ProgramHandle, fragment.ShaderHandle);
			glLinkProgram(ProgramHandle);

			int success;
			char infoBuffer[1024];
			glGetProgramiv(ProgramHandle, GL_LINK_STATUS, &success);

			if (!success) {
				glGetShaderInfoLog(ProgramHandle, 1024, NULL, infoBuffer);

				std::cout << "SHADER LINK ERROR:\n";
				std::cout << "\tVertex Shader: " << vertex.ResourcePath << "\n";
				std::cout << "\tFragment Shader: " << fragment.ResourcePath << "\n";

				ProgramValid = false;
			}

			ProgramValid = true;
		}
		else {
			ProgramValid = false;
		}
	}

	ShaderProgram::~ShaderProgram() {
		//glDeleteProgram(ProgramHandle);
	}

	void ShaderProgram::Use() {
		if (!ProgramValid) {
			std::cout << "Error: Attempted to use invalid shader program!\n";
			return;
		}

		glUseProgram(ProgramHandle);
	}

}