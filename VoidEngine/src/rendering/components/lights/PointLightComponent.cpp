//STD Headers

//Library Headers

//Void Engine Headers
#include "rendering/components/lights/PointLightComponent.h"

namespace core {

	ENABLE_FACTORY(PointLightComponent, Component)

	PointLightComponent::PointLightComponent() : intensity(1.0f), color(1,1,1,1), range(0.0f) {

	}

	void PointLightComponent::Initialize() {
		if (configData.find("color") != configData.end()) {
			auto vec = configData["color"];
			color = { vec[0], vec[1], vec[2], vec[3] };
		}

		if (configData.find("intensity") != configData.end()) {
			intensity = configData["intensity"];
		}

		if (configData.find("radius") != configData.end()) {
			intensity = configData["radius"];
		}
	}

}