#pragma once
//STD Headers
#include <vector>

//Library Headers

//Void Engine Headers
#include "core/rendering/components/CameraComponent.h"

namespace core {

	class ShipCamera : public core::CameraComponent {
		/**
		 * Declare custom RTTI support
		 */
		TYPE_INFO_DECL(ShipCamera)

	public:
		/**
		 * Constructor
		 */
		ShipCamera() = default;

		/**
		 * Destructor
		 */
		~ShipCamera();

		/**
		 * Orients camera to match entity rotation
		 */
		void Initialize() override;

		/**
		 * Defines how a component processes updates
		 * @param deltaSeconds the time elapsed since the previous tick
		 */
		virtual void Tick(float deltaTime);

	private:
		/** Orientation to maintain while ship is maneuvering */
		math::Quaternion m_SpawnOrientation;

		/** This camera's field of view */
		float m_FOV;
	};

}