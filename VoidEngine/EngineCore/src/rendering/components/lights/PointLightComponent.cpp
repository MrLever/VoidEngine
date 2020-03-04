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
		if (ConfigData.find("color") != ConfigData.end()) {
			auto vec = ConfigData["color"];
			m_Color = { vec[0], vec[1], vec[2], vec[3] };
		}

		if (ConfigData.find("intensity") != ConfigData.end()) {
			m_Intensity = ConfigData["intensity"];
		}

		if (ConfigData.find("radius") != ConfigData.end()) {
			m_Intensity = ConfigData["radius"];
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