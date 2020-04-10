//STD Headers

//Library Headers

//Void Engine Headers
#include "rendering/components/lights/PointLightComponent.h"

namespace core {
	TYPE_INFO_IMPL(PointLightComponent)

	ENABLE_FACTORY(PointLightComponent, Component)

	PointLightComponent::PointLightComponent() : m_Intensity(0.0f), m_Radius(0.0f) {

	}

	void PointLightComponent::Initialize() {
		if (configData.find("color") != configData.end()) {
			auto vec = configData["color"];
			m_Color = { vec[0], vec[1], vec[2], vec[3] };
		}

		if (configData.find("intensity") != configData.end()) {
			m_Intensity = configData["intensity"];
		}

		if (configData.find("radius") != configData.end()) {
			m_Intensity = configData["radius"];
		}
	}

	math::Vector4 PointLightComponent::GetColor() const {
		return m_Color;
	}

	float PointLightComponent::GetIntensity() const {
		return m_Intensity;
	}

	float PointLightComponent::GetRadius() const {
		return m_Radius;
	}
}