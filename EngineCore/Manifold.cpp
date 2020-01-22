//STD Headers

//Library Headers

//Void Engine Headers
#include "Manifold.h"
#include "ColliderComponent.h"
#include "EngineMath/Vector.h"

namespace core {
	Manifold::Manifold() 
		: ColliderA(nullptr), ColliderB(nullptr), 
		PenetrationDistance(0.0f), CollisionNormal() {

	}
}