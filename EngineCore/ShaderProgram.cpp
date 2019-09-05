//STD Headers

//Library Headers

//Void Engine Headers
#include "ShaderProgram.h"

namespace EngineCore {

	ShaderProgram::ShaderProgram(const std::string& name, Shader& vertex, Shader& fragment) 
		: ProgramName(std::move(name)) {

		vertex.Compile();


		ProgramHandle = glCreateProgram();
		glAttachShader(ProgramHandle, vertex.ShaderHandle);
		glAttachShader(ProgramHandle, fragment.ShaderHandle);
		glLinkProgram(ProgramHandle);

		int success;
		char infoBuffer[1024];
		glGetShaderiv(ProgramHandle, GL_LINK_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(ProgramHandle, 1024, NULL, infoBuffer);

			std::cout << "SHADER LINK ERROR:\n";
			std::cout << "\tVertex Shader: " << vertex.ShaderName << "\n";
			std::cout << "\tFragment Shader: " << fragment.ShaderName << "\n";

			ProgramValid = false;
		}

		ProgramValid = true;
	}

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(ProgramHandle);
	}

	void ShaderProgram::Use() {
		glUseProgram(ProgramHandle);
	}

}