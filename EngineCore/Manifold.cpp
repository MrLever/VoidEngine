//STD Headers

//Library Headers

//Void Engine Headers
#include "Manifold.h"
#include "Entity.h"
#include "EngineMath/Vector.h"

namespace core {
	Manifold::Manifold() 
		: EntityA(nullptr), EntityB(nullptr), 
		PenetrationDistance(0.0f), CollisionNormal() {

	}
}