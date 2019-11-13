//STD Headers

//Library Headers

//Void Engine Headers
#include "SphereCollider.h"
#include "AABBCollider.h"
#include "Factory.h"
#include "Logger.h"

namespace core {

	ENABLE_FACTORY(SphereCollider, ColliderComponent)

	SphereCollider::SphereCollider() : Radius(1.0) {

	}

	SphereCollider::SphereCollider(float r) : Radius(r) {

	}

	void SphereCollider::Initialize() {
		;
	}

	float SphereCollider::GetRadius() {
		return Radius;
	}

}