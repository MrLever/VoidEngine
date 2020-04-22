#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "math/Vector.h"
#include "core/rendering/components/lights/DirectionalLightComponent.h"
#include "core/rendering/components/lights/PointLightComponent.h"
#include "core/rendering/components/lights/SpotlightComponent.h"

namespace core {

	/**
	 * Struct used to define the totality of the lighting enviornment in a scene
	 */
	struct LightingEnvironment {
		math::Vector4 AmbientLightColor;
		float AmbientLightIntensity;
		std::vector<DirectionalLightComponent*> DirectionalLights;
		std::vector<PointLightComponent*> PointLights;
		std::vector<SpotlightComponent*> SpotLights;
	};

}