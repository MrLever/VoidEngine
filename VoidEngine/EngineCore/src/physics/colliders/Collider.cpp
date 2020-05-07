//STD Headers

//Library Headers

//Void Engine Headers
#include "physics/colliders/Collider.h"

namespace core {

	Collider::Collider() {

	}

	void Collider::SupplyEntityScale(const math::Vector3& entityScale) {
		this->entityScale = &entityScale;
	}

}