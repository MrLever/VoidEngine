//STD Headers

//Library Headers

//Void Engine Headers
#include "Collider.h"

namespace core {

	Collider::Collider() {

	}

	void Collider::SetConfigData(const nlohmann::json& data) {
		ShapeData = data;
	}

}