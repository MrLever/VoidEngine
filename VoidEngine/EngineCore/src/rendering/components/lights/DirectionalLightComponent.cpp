#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "rendering/components/lights/DirectionalLightComponent.h"

namespace core {
	TYPE_INFO_IMPL(DirectionalLightComponent)

	ENABLE_FACTORY(DirectionalLightComponent, Component)

	DirectionalLightComponent::DirectionalLightComponent() : intensity(0.0f) {

	}

	void DirectionalLightComponent::Initialize() {
		if (configData.find("direction") != configData.end()) {
			auto vec = configData["direction"];
			direction = { vec[0], vec[1], vec[2] };
		}

		if (configData.find("color") != configData.end()) {
			auto vec = configData["color"];
			color = { vec[0], vec[1], vec[2], vec[3] };
		}

		if (configData.find("intensity") != configData.end()) {
			intensity = configData["intensity"];
		}
	}

}