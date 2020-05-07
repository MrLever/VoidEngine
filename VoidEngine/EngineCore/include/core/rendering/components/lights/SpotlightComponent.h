#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/gameplay_framework/Component.h"

namespace core {
	class SpotlightComponent : public Component {
		/**
		 * Declare custom RTTI support
		 */
		ENABLE_RTTI(SpotlightComponent)

	public:
		/** Color of the spotlight */
		math::Vector4 color;

		/** The view angle in which the light will be at full intensity */
		float viewAngle;

		/** The number of degrees added to the view angle to create an outer cone for light to attenuate to 0 */
		float fadeAngle;

		/** Amount of energy in the light */
		float intensity;

		/** Max range of the spotlight */
		float range;

		/**
		 * Constructor
		 */
		SpotlightComponent();

		/**
		 * Destructor
		 */
		~SpotlightComponent() = default;

		/**
		 * Reads light data
		 */
		void Initialize() override;

	};
}