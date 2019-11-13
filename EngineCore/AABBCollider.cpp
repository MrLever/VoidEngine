//STD Headers

//Library Headers

//Void Engine Headers
#include "AABBCollider.h"
#include "SphereCollider.h"
#include "Factory.h"
#include "Logger.h"

namespace core {

	ENABLE_FACTORY(AABBCollider, ColliderComponent)

	void AABBCollider::Initialize() {
		;
	}

}
