#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "math/Vector.h"

#include "core/gameplay_framework/Component.h"

namespace core {
	/**
	 * @class DirectionalLightComponent
	 * @brief Allows an entity to bring directional lighting into a scene
	 */
	class DirectionalLightComponent : public Component {
		/**
		 * Declare custom RTTI support
		 */
		ENABLE_RTTI(DirectionalLightComponent)

	public:
		/** Direction of the directional light */
		math::Vector3 direction;

		/** Color of the directional light */
		math::Vector4 color;

		/** Amount of energy in light */
		float intensity;

		/**
		 * Constructor
		 */
		DirectionalLightComponent();

		/**
		 * Destructor
		 */
		~DirectionalLightComponent() = default;

		/**
		 * Loads light settings into object from specified settings
		 */
		void Initialize() override;

	};
}