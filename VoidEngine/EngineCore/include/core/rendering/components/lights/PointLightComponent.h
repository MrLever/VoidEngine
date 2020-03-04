#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "math/Vector.h"

#include "core/gameplay_framework/Component.h"

namespace core {
	/**
	* @class PointLightComponent
	* @brief Allows an entity to bring point lighting into a scene
	*/
	class PointLightComponent : public Component {
		/**
		 * Declare custom RTTI support
		 */
		TYPE_INFO_DECL(PointLightComponent)

	public:
		/**
		 * Constructor
		 */
		PointLightComponent();
		
		/**
		 * Destructor
		 */
		~PointLightComponent() = default;

		/**
		 * Loads light settings into object from specified settings
		 */
		void Initialize() override;

		/**
		 * Color Accessor
		 */
		math::Vector4 GetColor() const;

		/**
		 * Intensity Accessor
		 */
		float GetIntensity() const;

		/**
		 * Intensity Accessor
		 */
		float GetRadius() const;

	private:
		/** Color of the directional light */
		math::Vector4 m_Color;

		/** Amount of energy in light */
		float m_Intensity;

		/** bounding radius of point light's influence */
		float m_Radius;
	};

}