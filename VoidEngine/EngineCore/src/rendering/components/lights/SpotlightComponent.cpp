//STD Headers

//Library Headers

//Void Engine Headers
#include "rendering/components/lights/SpotlightComponent.h"

namespace core {

	ENABLE_FACTORY(SpotlightComponent, Component)

	SpotlightComponent::SpotlightComponent() 
		: color({ 1.0f, 1.0f, 1.0f, 1.0f }), intensity(1.0f), viewAngle(12.5f), fadeAngle(5.0f), range(0) {
	
	}

	void SpotlightComponent::Initialize() {
		if (DataContainsKey("color")) {
			color = {
				configData["color"][0],
				configData["color"][1],
				configData["color"][2],
				configData["color"][3]
			};
		}

		if (DataContainsKey("intensity")) {
			intensity = configData["intensity"];
		}

		if (DataContainsKey("viewAngle")) {
			viewAngle = configData["viewAngle"];
		}

		if (DataContainsKey("fadeAngle")) {
			fadeAngle = configData["fadeAngle"];
		}

		if (DataContainsKey("range")) {
			range = configData["range"];
		}
	}

}
