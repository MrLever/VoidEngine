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

	utils::Name Collider::GetStaticTypename() {
		return utils::Name("Collider");
	}

}