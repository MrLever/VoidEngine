#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "math/Vector.h"
#include "math/Rotator.h"

#include "core/gameplay_framework/Component.h"
#include "core/rendering/Model.h"

namespace core {
	/**
	 * @class DirectionalLightComponent
	 * @brief Allows an entity to bright directional lighting into a scene
	 */
	class DirectionalLightComponent : public Component {
		/**
		 * Declare custom RTTI support
		 */
		TYPE_INFO_DECL(DirectionalLightComponent)

	public:
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

		/**
		 * Direction Accessor
		 */
		math::Vector3 GetDirection() const;

		/**
		 * Color Accessor
		 */
		math::Vector4 GetColor() const;

		/**
		 * Intensity Accessor
		 */
		float GetIntensity() const;

	private:
		/** Direction of the directional light */
		math::Vector3 m_Direction;

		/** Color of the directional light */
		math::Vector4 m_Color;

		/** Amount of energy in light */
		float m_Intensity;

	};
}