//STD Headers

//Library Headers

//Void Engine Headers
#include "rendering/ShaderProgram.h"
#include "utils/Logger.h"

namespace core {

	ShaderProgram::ShaderProgram(const std::string& name, Shader* vertex, Shader* fragment) 
		: m_ProgramName(name), m_ProgramHandle(-1) {

		vertex->Initialize();
		fragment->Initialize();

		if (vertex->IsValid() && fragment->IsValid()) {

			m_ProgramHandle = glCreateProgram();
			glAttachShader(m_ProgramHandle, vertex->m_ShaderHandle);
			glAttachShader(m_ProgramHandle, fragment->m_ShaderHandle);
			glLinkProgram(m_ProgramHandle);

			int success;
			char infoBuffer[1024];
			glGetProgramiv(m_ProgramHandle, GL_LINK_STATUS, &success);

			if (!success) {
				glGetShaderInfoLog(m_ProgramHandle, 1024, NULL, infoBuffer);
				
				std::stringstream errorMessage;

				errorMessage << "SHADER LINK ERROR:\n";
				errorMessage << "\tVertex Shader: " << vertex->ResourcePath << "\n";
				errorMessage << "\tFragment Shader: " << fragment->ResourcePath << "\n";

				utils::Logger::LogError(errorMessage.str());
				m_ProgramValid = false;
			}

			m_ProgramValid = true;
		}
		else {
			m_ProgramValid = false;
		}

		delete vertex;
		delete fragment;
	}

	ShaderProgram::~ShaderProgram() {
		
	}

	void ShaderProgram::Use() {
		if (!m_ProgramValid) {
			utils::Logger::LogError("Attempted to use invalid shader program!");
			return;
		}

		glUseProgram(m_ProgramHandle);
	}

	void ShaderProgram::SetUniform(const std::string& uniformName, float value) {
		glProgramUniform1f(m_ProgramHandle, GetUniformLocation(uniformName), value);
	}

	void ShaderProgram::SetUniform(const std::string& uniformName, unsigned int value) {
		glProgramUniform1ui(m_ProgramHandle, GetUniformLocation(uniformName), value);
	}

	void ShaderProgram::SetUniform(const std::string& uniformName, int value) {
		glProgramUniform1i(m_ProgramHandle, GetUniformLocation(uniformName), value);
	}

	void ShaderProgram::SetUniform(const std::string& uniformName, bool value) {
		SetUniform(uniformName, (int)value);
	}

	void ShaderProgram::SetUniform(const std::string& uniformName, const glm::mat3& value) {
		glProgramUniformMatrix3fv(
			m_ProgramHandle,
			GetUniformLocation(uniformName),
			1,
			GL_FALSE,
			glm::value_ptr(value)
		);
	}

	void ShaderProgram::SetUniform(const std::string& uniformName, const glm::mat4& value) {
		glProgramUniformMatrix4fv(
			m_ProgramHandle, 
			GetUniformLocation(uniformName), 
			1, 
			GL_FALSE, 
			glm::value_ptr(value)
		);
	}

	void ShaderProgram::SetUniform(const std::string& uniformName, const math::Vector3& value) {
		float vec[3] = { value.X, value.Y, value.Z };

		glProgramUniform3fv(
			m_ProgramHandle,
			GetUniformLocation(uniformName),
			1,
			vec
		);
	}

	void ShaderProgram::SetUniform(const std::string& uniformName, const math::Vector4& value) {
		//Reduce to C array
		float vec[4] = { value.X, value.Y, value.Z, value.W };

		//Send to OpenGL
		glProgramUniform4fv(
			m_ProgramHandle, 
			GetUniformLocation(uniformName), 
			1, 
			vec
		);
	}

	GLint ShaderProgram::GetUniformLocation(const std::string& uniformName){
		return glGetUniformLocation(m_ProgramHandle, uniformName.c_str());
	}

}