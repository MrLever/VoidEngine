#pragma once
//STD Headers
#include <vector>

//Library Headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Void Engine Headers
#include "Component.h"
#include "Vector.h"
#include "WindowManager.h"

namespace core {
	class CameraComponent : public Component {
	public:
		/**
		 * Constructor
		 * @param parent This component's parent entity
		 */
		CameraComponent(Entity* parent);

		/**
		 * Destructor
		 */
		~CameraComponent();

		/**
		 * Defines how a component processes updates
		 * @param deltaSeconds the time elapsed since the previous tick
		 */
		virtual void Tick(float deltaTime);

		/**
		 * Allows caller to access this camera's view matrix
		 * @return ViewMatrix
		 */
		glm::mat4 GetViewMatrix() const;
		
		/**
		 * Allows caller to access this camera's projection matrix
		 * @return ProjectionMatrix
		 */
		glm::mat4 GetProjectionMatrix() const;

		/**
		 * Allows user to set this camera's FOV
		 */
		void SetFOV(float fov);

		/**
		 * Getter for this camera's FOV
		 */
		float GetFOV();

		/**
		 * Function to update the camera's Projection Matrix in response
		 * to a change in window size
		 */
		void UpdateProjectionMatrix();

	private:

		/** This camera's projection matrix */
		glm::mat4 ProjectionMatrix;

		/** This camera's view matrix */
		glm::mat4 ViewMatrix;

		/** This camera's field of view */
		float FOV;

		/** Vector to represent the direction the camera is looking */
		math::Vector3 LookDirection;
		
		/** Vector to represent the up direction for the camera */
		math::Vector3 Up;

	};

}