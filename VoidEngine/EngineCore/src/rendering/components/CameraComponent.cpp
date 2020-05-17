//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/factory/Factory.h"

#include "rendering/Components/CameraComponent.h"

namespace core {

	ENABLE_FACTORY(CameraComponent, Component)

	CameraComponent::CameraComponent()
		: m_ProjectionMatrix(1), m_ViewMatrix(1), m_FOV(45.0), m_Near(0.1f), m_Far(1000.0f), m_Name("Camera") {

	}

	CameraComponent::~CameraComponent() {
	
	}

	void CameraComponent::Initialize() {
		if (configData.find("name") != configData.end()) {
			m_Name = configData["name"];
		}

		if (configData.find("near") != configData.end()) {
			m_Near = configData["near"];
		}

		if (configData.find("far") != configData.end()) {
			m_Far = configData["far"];
		}
	}
	
	void CameraComponent::Tick(float deltaTime) {
		auto lookDirection = parent->GetForward();
		auto up = parent->GetUp();
		auto target = parent->GetPosition() + lookDirection;
		
		//Set view matrix for this frame
		auto position = parent->GetPosition();
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
			m_Near,
			m_Far
		);
	}

	utils::Name CameraComponent::GetName() const {
		return m_Name;
	}

}