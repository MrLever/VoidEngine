//STD Headers

//Library Headers

//Void Engine Headers
#include "Collider.h"

namespace core {

	// Static variable initialization
	const float Collider::COLLISION_EPSILON = 0.0001f;

	Collider::Collider() {

	}

	void Collider::SetConfigData(const nlohmann::json& data) {
		ShapeData = data;
	}

	utils::Name Collider::GetStaticTypename() {
		return utils::Name("Collider");
	}

}