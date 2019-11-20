//STD Headers

//Library Headers

//Void Engine Headers
#include "PhysicsBody.h"

namespace core {
	
	PhysicsBody::PhysicsBody() 
		: Velocity(), Force(), Mass(1), 
		  GravityScale(1), Density(1), Restitution(.5), 
		  PhysicsEnabled(true) {
		
	}

}
