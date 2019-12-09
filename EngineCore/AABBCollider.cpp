//STD Headers

//Library Headers

//Void Engine Headers
#include "AABBCollider.h"
#include "SphereCollider.h"

namespace core {
	TYPE_INFO_IMPL(AABBCollider)

	ENABLE_FACTORY(AABBCollider, Collider)

	AABBCollider::AABBCollider() {

	}

	void AABBCollider::Initialize() {
		MinExtent.X = ConfigData["min"][0].get<float>();
		MinExtent.Y = ConfigData["min"][1].get<float>();
		MinExtent.Z = ConfigData["min"][2].get<float>();

		MaxExtent.X = ConfigData["max"][0].get<float>();
		MaxExtent.Y = ConfigData["max"][1].get<float>();
		MaxExtent.Z = ConfigData["max"][2].get<float>();
	}

	math::Vector3 AABBCollider::GetMin() const {
		return MinExtent;
	}

	math::Vector3 AABBCollider::GetMax() const {
		return MaxExtent;
	}

}
