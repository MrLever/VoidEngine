//STD Headers
#include <cmath>
#include <iostream>

//Engine Headers
#include "Shader.h"
#include "TimeUtils.h"

//SuperVoid Headers
#include "CubeEntity.h"

namespace SuperVoid {
	CubeEntity::CubeEntity(const std::string& name) : Entity(name) {
		Velocity = 0.05f;
	}

	CubeEntity::~CubeEntity() {

	}

	void CubeEntity::BeginPlay() {
		std::cout << ID.StringID << " began play\n";
	}

	void CubeEntity::Tick(float deltaSeconds) {
	}
	
	void CubeEntity::Terminate() {

	}
}