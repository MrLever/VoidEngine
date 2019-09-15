//STD Headers

//Engine Headers
#include "Shader.h"

//SuperVoid Headers
#include "CubeEntity.h"

namespace SuperVoid {
	CubeEntity::CubeEntity(const std::string& name) : Entity(name) {

	}

	CubeEntity::~CubeEntity() {

	}

	void CubeEntity::BeginPlay() {
		std::cout << "Cube Began Play";
	}

	void CubeEntity::Tick(double deltaSeconds) {
	
	}
	
	void CubeEntity::Draw() {
		
	}
	
	void CubeEntity::Terminate() {

	}
}