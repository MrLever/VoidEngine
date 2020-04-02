#pragma once
//STD Headers
#include <vector>

//Library Headers

//Void Engine Headers
#include "core/rendering/components/CameraComponent.h"

namespace SuperVoid {

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
		 * Initialize Camera
		 */
		void Initialize() override;

		/**
		 * Update entity
		 */
		void Tick(float deltaTime) override;

	protected:
		math::Quaternion m_SpawnOrientation;
	};

}