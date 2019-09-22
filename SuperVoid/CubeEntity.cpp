//STD Headers
#include <cmath>

//Engine Headers
#include "Shader.h"
#include "TimeUtils.h"

//SuperVoid Headers
#include "CubeEntity.h"

namespace SuperVoid {
	CubeEntity::CubeEntity(const std::string& name) : Entity(name) {

	}

	CubeEntity::~CubeEntity() {

	}

	void CubeEntity::BeginPlay() {
		std::cout << ID.StringID << " began play\n";
	}

	void CubeEntity::Tick(float deltaSeconds) {
		auto deltaHeight = deltaSeconds * 2 * (float)std::sin(EngineUtils::GetGameTime());

		Position.Y = Position.Y + deltaHeight;
	}
	
	void CubeEntity::Terminate() {

	}
}