#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "rendering/components/lights/DirectionalLightComponent.h"

namespace core {
	TYPE_INFO_IMPL(DirectionalLightComponent)

	ENABLE_FACTORY(DirectionalLightComponent, Component)

	DirectionalLightComponent::DirectionalLightComponent() : m_Intensity(0.0f) {

	}

	void DirectionalLightComponent::Initialize() {
		if (configData.find("direction") != configData.end()) {
			auto vec = configData["direction"];
			m_Direction = { vec[0], vec[1], vec[2] };
		}

		if (configData.find("color") != configData.end()) {
			auto vec = configData["color"];
			m_Color = { vec[0], vec[1], vec[2], vec[3] };
		}

		if (configData.find("intensity") != configData.end()) {
			m_Intensity = configData["intensity"];
		}
	}

	math::Vector3 DirectionalLightComponent::GetDirection() const {
		return m_Direction;
	}

	math::Vector4 DirectionalLightComponent::GetColor() const {
		return m_Color;
	}

	float DirectionalLightComponent::GetIntensity() const {
		return m_Intensity;
	}
}