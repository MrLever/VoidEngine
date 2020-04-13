//STD Headers
#include <vector>

//Library Headers

//Void Engine Headers
#include "ShipCamera.h"

namespace SuperVoid {
	TYPE_INFO_IMPL(ShipCamera)

	ENABLE_FACTORY(ShipCamera, core::Component)

	ShipCamera::~ShipCamera() {

	}

	void ShipCamera::Initialize() {
		core::CameraComponent::Initialize();
		m_SpawnOrientation = parent->GetRotation();
	}

	void ShipCamera::Tick(float deltaTime) {
		parent->SetRotation(m_SpawnOrientation);
		CameraComponent::Tick(deltaTime);
	}
	
}
