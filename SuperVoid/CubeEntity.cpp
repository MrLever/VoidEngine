//STD Headers
#include <cmath>
#include <iostream>

//Engine Headers
#include "Shader.h"
#include "TimeUtils.h"

//SuperVoid Headers
#include "CubeEntity.h"
#include "Logger.h"
#include "Factory.h"

namespace SuperVoid {

	ENABLE_FACTORY(CubeEntity, core::Entity)

	CubeEntity::CubeEntity() {
		Velocity = 0.05f;
		Body.PhysicsEnabled = false;
	}

	CubeEntity::~CubeEntity() {

	}

	void CubeEntity::Initialize() {
		Entity::Initialize();
	}

	void CubeEntity::BeginPlay() {
		utils::Logger::LogInfo(ID.StringID + " began play");
	}

	void CubeEntity::Tick(float deltaSeconds) {

	}
	
	void CubeEntity::Terminate() {

	}

}