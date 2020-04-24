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
		/** Color of the point light */
		math::Vector4 color;

		/** bounding radius of point light's influence */
		float range;

		/** Amount of energy in light */
		float intensity;

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

	};

}