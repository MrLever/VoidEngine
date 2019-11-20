//STD Headers

//Library Headers

//Void Engine Headers
#include "PhysicsBody.h"

namespace core {
	
	PhysicsBody::PhysicsBody() 
		: Velocity(), Force(), Mass(1), InverseMass(1),
		  GravityScale(1), Density(1), Restitution(.5), 
		  PhysicsEnabled(true) {

	}

	void PhysicsBody::SetMass(float mass) {
		Mass = mass;
		if (mass = 0) {
			InverseMass = 0;
		}
		else {
			InverseMass = 0;
		}
	}

}
