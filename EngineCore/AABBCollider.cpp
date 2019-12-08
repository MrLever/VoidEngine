//STD Headers

//Library Headers

//Void Engine Headers
#include "AABBCollider.h"
#include "SphereCollider.h"

namespace core {

	ENABLE_FACTORY(AABBCollider, Collider)

	AABBCollider::AABBCollider() {

	}

	void AABBCollider::Initialize() {
		MinExtent.X = ShapeData["min"][0].get<float>();
		MinExtent.Y = ShapeData["min"][1].get<float>();
		MinExtent.Z = ShapeData["min"][2].get<float>();

		MaxExtent.X = ShapeData["max"][0].get<float>();
		MaxExtent.Y = ShapeData["max"][1].get<float>();
		MaxExtent.Z = ShapeData["max"][2].get<float>();
	}

	math::Vector3 AABBCollider::GetMin() const {
		return MinExtent;
	}

	math::Vector3 AABBCollider::GetMax() const {
		return MaxExtent;
	}

	utils::Name AABBCollider::GetTypename() const {
		return utils::Name("AABBCollider");
	}

	utils::Name AABBCollider::GetStaticTypename() {
		return utils::Name("AABBCollider");
	}

}
