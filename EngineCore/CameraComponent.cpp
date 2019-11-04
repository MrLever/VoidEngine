//STD Headers

//Library Headers

//Void Engine Headers
#include "CameraComponent.h"
#include "Factory.h"

namespace core {

	ENABLE_FACTORY(CameraComponent, Component)

	CameraComponent::CameraComponent(Entity* parent) 
		: Component(parent), ProjectionMatrix(1), ViewMatrix(1), FOV(45.0), Up(0,1,0) {
		
		UpdateProjectionMatrix();
		LookDirection = math::Vector3(0, 0, -1);
	}

	CameraComponent::~CameraComponent() {
	
	}

	void CameraComponent::Tick(float deltaTime) {
		//Update position to reflect parent's position
		Position = Parent->GetPostion();
		Rotation = Parent->GetRotation();

		LookDirection = Rotation.ToVector();
		//LookDirection = math::Vector3(0, 0, -1);

		auto target = Position + LookDirection;
		
		//Set view matrix for this frame
		ViewMatrix = glm::lookAt(
			glm::vec3(Position.X, Position.Y, Position.Z),
			glm::vec3(target.X, target.Y, target.Z),
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

	float CameraComponent::GetFOV() {
		return FOV;
	}

	void CameraComponent::UpdateProjectionMatrix() {
		float windowWidth = (float)Window::GetActiveWindow()->GetWindowWidth();
		float windowHeight = (float)Window::GetActiveWindow()->GetWindowHeight();

		ProjectionMatrix = glm::perspective<float>(
			glm::radians(FOV),
			windowWidth / windowHeight,
			0.1f,
			100.0f
		);
	}

}