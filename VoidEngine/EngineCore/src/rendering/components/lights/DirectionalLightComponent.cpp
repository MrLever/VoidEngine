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
		VE_ASSERT(false, "Function not implemented. Please do.")
		if (ConfigData.find("direction") != ConfigData.end()) {
			auto vec = ConfigData["direction"];
			m_Direction = { vec[0], vec[1], vec[2] };
		}

		if (ConfigData.find("color") != ConfigData.end()) {
			auto vec = ConfigData["color"];
			m_Color = { vec[0], vec[1], vec[2], vec[3] };
		}

		if (ConfigData.find("intensity") != ConfigData.end()) {
			m_Intensity = ConfigData["intensity"];
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