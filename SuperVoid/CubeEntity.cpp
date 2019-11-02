//STD Headers
#include <cmath>
#include <iostream>

//Engine Headers
#include "Shader.h"
#include "TimeUtils.h"

//SuperVoid Headers
#include "CubeEntity.h"
#include "Logger.h"

namespace SuperVoid {
	CubeEntity::CubeEntity() {
		Velocity = 0.05f;
	}

	CubeEntity::~CubeEntity() {

	}

	void CubeEntity::Initialize() {
		;
	}

	void CubeEntity::BeginPlay() {
		utils::Logger::LogInfo(ID.StringID + " began play");
	}

	void CubeEntity::Tick(float deltaSeconds) {

	}
	
	void CubeEntity::Terminate() {

	}
}