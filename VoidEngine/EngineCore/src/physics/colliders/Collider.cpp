//STD Headers

//Library Headers

//Void Engine Headers
#include "physics/colliders/Collider.h"

namespace core {

	TYPE_INFO_IMPL(Collider)

	Collider::Collider() {

	}

	void Collider::SupplyEntityScale(const math::Vector3& entityScale) {
		this->entityScale = &entityScale;
	}

}