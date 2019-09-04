//STD Headers

//Engine Headers

//SuperVoid Headers
#include "CubeEntity.h"

namespace SuperVoid {
	CubeEntity::CubeEntity(const std::string& name) : Entity(name) {
		auto verts = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f 
		};

		Model = EngineCore::GraphicsComponent(verts);

	}

	void CubeEntity::BeginPlay() {
	}

	void CubeEntity::Tick(double deltaSeconds) {
	}
	
	EngineCore::GraphicsComponent CubeEntity::Draw() {
		return Model;
	}
	
	void CubeEntity::Terminate() {
	}
}