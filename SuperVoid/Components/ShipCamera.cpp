//STD Headers
#include <vector>

//Library Headers

//Void Engine Headers
#include "ShipCamera.h"

namespace core {
	TYPE_INFO_IMPL(ShipCamera)

	ENABLE_FACTORY(ShipCamera, Component)

	ShipCamera::~ShipCamera() {

	}
	
	void ShipCamera::Initialize() {
		CameraComponent::Initialize();

		m_SpawnOrientation = m_Transform->GetRotation();
	}
	
	void ShipCamera::Tick(float deltaTime) {
		m_Transform->SetRotation(m_SpawnOrientation);
	}
}
