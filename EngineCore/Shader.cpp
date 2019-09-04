//STD Headers
#include <fstream>
#include <iostream>

//Library Headers

//Void Engine Headers
#include "Shader.h"

namespace EngineCore {
	Shader::Shader(const std::string& name, ShaderType type, const std::string& filePath) 
		: Resource(filePath), ShaderName(name), Type(type), ShaderHandle(-1) {

	}

	Shader::~Shader() {
		//When the shader is no longer needed, instruct OpenGL to discard it
		glDeleteShader(ShaderHandle);
	}

	bool Shader::Load() {
		std::ifstream ifs;
		std::string sourceBuffer;
		std::string lineBuffer;

		ifs.open(ResourcePath);
		if (!ifs.is_open()) {
			std::cout << "\n**ERROR** shader" << ResourcePath << "not found.";
			return false;
		}

		while (std::getline(ifs, lineBuffer)) {
			sourceBuffer += lineBuffer + "\n";
		}

		ifs.close();

		ShaderSource = sourceBuffer;
		return true;
	}
	
	bool Shader::LoadErrorResource() {
		ShaderSource = "";
		return false;
	}
}