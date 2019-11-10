//STD Headers

//Library Headers

//Void Engine Headers
#include "Collider.h"

namespace core {

	Collider::Collider() : Layer((unsigned)CollisionLayer::ALL) {

	}

	Collider::Collider(CollisionLayer layer) : Layer((unsigned)layer) {
	
	}

}
