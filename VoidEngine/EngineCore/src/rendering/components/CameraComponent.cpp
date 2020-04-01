//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/factory/Factory.h"

#include "rendering/Components/CameraComponent.h"

namespace core {
	TYPE_INFO_IMPL(CameraComponent)

	ENABLE_FACTORY(CameraComponent, Component)

	CameraComponent::CameraComponent()
		: m_ProjectionMatrix(1), m_ViewMatrix(1), m_FOV(45.0), m_Name("Camera") {

	}

	CameraComponent::~CameraComponent() {
	
	}

	void CameraComponent::Initialize() {
		if (ConfigData.find("name") != ConfigData.end()) {
			m_Name = ConfigData["name"];
		}
	}
	
	void CameraComponent::Tick(float deltaTime) {
		auto lookDirection = m_Transform->GetForward();
		auto up = m_Transform->GetUp();
		auto target = m_Transform->GetPosition() + lookDirection;
		
		//Set view matrix for this frame
		auto position = m_Transform->GetPosition();
		m_ViewMatrix = glm::lookAt(
			glm::vec3(position.X, position.Y, position.Z),
			glm::vec3(target.X, target.Y, target.Z),
			glm::vec3(up.X, up.Y, up.Z)
	    );
	}

	glm::mat4 CameraComponent::GetViewMatrix() const {
		return m_ViewMatrix;
	}

	glm::mat4 CameraComponent::GetProjectionMatrix() const {
		return m_ProjectionMatrix;
	}

	void CameraComponent::SetFOV(float fov) {
		m_FOV = fov;
	}

	float CameraComponent::GetFOV() {
		return m_FOV;
	}

	void CameraComponent::SetProjectionMatrix(Viewport viewport) {
		m_ProjectionMatrix = glm::perspective<float>(
			glm::radians(m_FOV),
			(float)viewport.Width / viewport.Height,
			0.1f,
			100.0f
		);
	}

	utils::Name CameraComponent::GetName() const {
		return m_Name;
	}

}