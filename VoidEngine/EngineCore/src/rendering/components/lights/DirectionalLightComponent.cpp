#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "rendering/components/lights/DirectionalLightComponent.h"

namespace core {
	TYPE_INFO_IMPL(DirectionalLightComponent)

	ENABLE_FACTORY(DirectionalLightComponent, Component)

	void DirectionalLightComponent::Initialize() {
		VE_ASSERT(false, "Function not implemented. Please do.")
		if (ConfigData.find("direction") != ConfigData.end()) {
		
		}
	}
}