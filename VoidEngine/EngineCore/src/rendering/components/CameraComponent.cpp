//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/factory/Factory.h"

#include "rendering/Components/CameraComponent.h"

namespace core {
	TYPE_INFO_IMPL(CameraComponent)

	ENABLE_FACTORY(CameraComponent, Component)

	CameraComponent::CameraComponent()
		: m_ProjectionMatrix(1), m_ViewMatrix(1), m_FOV(45.0), m_UpDirection(0,1,0), m_Name("Camera") {

	}

	CameraComponent::~CameraComponent() {
	
	}

	void CameraComponent::Initialize() {
		m_LookDirection = m_Transform->Rotation.ToVector();

		if (ConfigData.find("name") != ConfigData.end()) {
			m_Name = ConfigData["name"];
		}
	}

	void CameraComponent::Tick(float deltaTime) {
		m_LookDirection = m_Transform->Rotation.ToVector();

		auto target = m_Transform->Position + m_LookDirection;
		
		//Set view matrix for this frame
		m_ViewMatrix = glm::lookAt(
			glm::vec3(m_Transform->Position.X, m_Transform->Position.Y, m_Transform->Position.Z),
			glm::vec3(target.X, target.Y, target.Z),
			glm::vec3(m_UpDirection.X, m_UpDirection.Y, m_UpDirection.Z)
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