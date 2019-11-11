#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Vector.h"

namespace core {

	struct PhysicsBody {
		/**
		 * Constructor
		 */
		PhysicsBody();

		/** The Entity's current velocity */
		math::Vector3 Velocity;

		/** Represents the sum of all the forces acting on the parent */
		math::Vector3 Force;

		/** The parent's mass */
		float Mass;

		/** Scales how much gravity effects the parent */
		float GravityScale;

		/** Density of parent */
		float Density;

		/** Elasticity of parent */
		float Restitution;
	};
}

