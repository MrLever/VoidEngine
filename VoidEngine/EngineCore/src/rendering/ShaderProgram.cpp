//STD Headers

//Library Headers

//Void Engine Headers
#include "rendering/ShaderProgram.h"
#include "utils/Logger.h"

namespace core {

	ShaderProgram::ShaderProgram(const std::string& name, Shader* vertex, Shader* fragment) 
		: ProgramName(name), ProgramHandle(-1) {

		vertex->Initialize();
		fragment->Initialize();

		if (vertex->IsValid() && fragment->IsValid()) {

			ProgramHandle = glCreateProgram();
			glAttachShader(ProgramHandle, vertex->ShaderHandle);
			glAttachShader(ProgramHandle, fragment->ShaderHandle);
			glLinkProgram(ProgramHandle);

			int success;
			char infoBuffer[1024];
			glGetProgramiv(ProgramHandle, GL_LINK_STATUS, &success);

			if (!success) {
				glGetShaderInfoLog(ProgramHandle, 1024, NULL, infoBuffer);
				
				std::stringstream errorMessage;

				errorMessage << "SHADER LINK ERROR:\n";
				errorMessage << "\tVertex Shader: " << vertex->ResourcePath << "\n";
				errorMessage << "\tFragment Shader: " << fragment->ResourcePath << "\n";

				utils::Logger::LogError(errorMessage.str());
				ProgramValid = false;
			}

			ProgramValid = true;
		}
		else {
			ProgramValid = false;
		}

		delete vertex;
		delete fragment;
	}

	ShaderProgram::~ShaderProgram() {
		
	}

	void ShaderProgram::SetUniform(const std::string& uniformName, float value) {
		glProgramUniform1f(ProgramHandle, GetUniformLocation(uniformName), value);
	}

	void ShaderProgram::SetUniform(const std::string& uniformName, unsigned int value) {
		glProgramUniform1ui(ProgramHandle, GetUniformLocation(uniformName), value);
	}

	void ShaderProgram::SetUniform(const std::string& uniformName, int value) {
		glProgramUniform1i(ProgramHandle, GetUniformLocation(uniformName), value);
	}

	void ShaderProgram::SetUniform(const std::string& uniformName, bool value) {
		SetUniform(uniformName, (int)value);
	}

	void ShaderProgram::Use() {
		if (!ProgramValid) {
			utils::Logger::LogError("Attempted to use invalid shader program!");
			return;
		}

		glUseProgram(ProgramHandle);
	}

	void ShaderProgram::SetUniform(const std::string& uniformName, const glm::mat4& value) {
		glProgramUniformMatrix4fv(
			ProgramHandle, 
			GetUniformLocation(uniformName), 
			1, 
			GL_FALSE, 
			glm::value_ptr(value)
		);
	}

	void ShaderProgram::SetUniform(const std::string& uniformName, const math::Vector4& value) {
		//Reduce to C array
		float vec[4] = { value.X, value.Y, value.Z, value.W };

		//Send to OpenGL
		glProgramUniform4fv(
			ProgramHandle, 
			GetUniformLocation(uniformName), 
			1, 
			vec
		);

	}

	GLint ShaderProgram::GetUniformLocation(const std::string& uniformName){
		return glGetUniformLocation(ProgramHandle, uniformName.c_str());
	}

}