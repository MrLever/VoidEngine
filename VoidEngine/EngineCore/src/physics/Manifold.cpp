//STD Headers

//Library Headers

//Void Engine Headers
#include "math/Vector.h"

#include "gameplay_framework/Entity.h"
#include "physics/Manifold.h"

namespace core {
	Manifold::Manifold() 
		: EntityA(nullptr), EntityB(nullptr), 
		PenetrationDistance(0.0f), m_CollisionNormal() {

	}
}