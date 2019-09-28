//STD Headers

//Library Headers

//Void Engine Headers
#include "CameraComponent.h"

namespace EngineCore {

	CameraComponent::CameraComponent(Entity* parent) 
		: Component(parent), ProjectionMatrix(1), ViewMatrix(1), FOV(45.0) {
		
		UpdateProjectionMatrix();
		LookDirection = Rotation.ToVector();
		LookDirection = LookDirection.Normalize();
	}

	CameraComponent::~CameraComponent() {
	
	}

	void CameraComponent::Tick(float deltaTime) {
		Position = Parent->GetPostion();
		LookDirection = Rotation.ToVector();

		auto target = Position + LookDirection;
		ViewMatrix = glm::lookAt(
			glm::vec3(Position.X, Position.Y, Position.Z),
			glm::vec3(target.X, target.Y, target.X),
			glm::vec3(Up.X, Up.Y, Up.Z)
	    );

	}

	glm::mat4 CameraComponent::GetViewMatrix() const {
		return ViewMatrix;
	}

	glm::mat4 CameraComponent::GetProjectionMatrix() const {
		return ProjectionMatrix;
	}

	void CameraComponent::SetFOV(float fov) {
		FOV = fov;
		
		UpdateProjectionMatrix();
	}

	void CameraComponent::UpdateProjectionMatrix() {
		auto windowWidth = WindowManager::GetActiveWindow()->GetWindowWidth();
		auto windowHeight = WindowManager::GetActiveWindow()->GetWindowWidth();

		ProjectionMatrix = glm::perspective<float>(
			glm::radians(FOV),
			(float)(windowWidth / windowHeight),
			0.1f,
			100.0f
		);
	}

}