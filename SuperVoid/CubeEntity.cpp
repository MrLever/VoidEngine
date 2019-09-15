//STD Headers

//Engine Headers
#include "Shader.h"

//SuperVoid Headers
#include "CubeEntity.h"

namespace SuperVoid {
	CubeEntity::CubeEntity(const std::string& name) : Entity(name) {
		auto verts = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f 
		};

		EngineCore::Shader vertShader("SimpleVertexShader", EngineCore::ShaderType::VERTEX, "foo");
		EngineCore::Shader fragShader("SimpleFragShader", EngineCore::ShaderType::FRAGMENT, "bar");

		GraphicsData = new EngineCore::GraphicsComponent(verts, EngineCore::ShaderProgram("Simple program", vertShader, fragShader));
	}

	CubeEntity::~CubeEntity() {

	}

	void CubeEntity::BeginPlay() {
	
	}

	void CubeEntity::Tick(double deltaSeconds) {
	
	}
	
	void CubeEntity::Draw() {
		
	}
	
	void CubeEntity::Terminate() {

	}
}