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
	private:
		/** Direction of the directional light */
		math::Vector3 m_Direction;

		/** Color of the directional light */
		math::Vector4 m_Color;

		/** Amount of energy in light */
		float m_Intensity;
	};

}