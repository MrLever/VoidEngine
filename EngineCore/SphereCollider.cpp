//STD Headers

//Library Headers

//Void Engine Headers
#include "SphereCollider.h"

namespace core {
	ENABLE_FACTORY(SphereCollider, Collider)

	SphereCollider::SphereCollider() : Radius(0.0f) {

	}

	void SphereCollider::Initialize() {
		Radius = ShapeData["radius"].get<float>();
	}

	float SphereCollider::GetRadius() {
		return Radius;
	}

}