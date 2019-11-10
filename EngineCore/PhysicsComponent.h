#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Component.h"
#include "Vector.h"

namespace core {

	/**
	 * @class Physics Component 
	 * @brief Define's the physical properties of its parent entity
	 *        for use in physics calculations
	 */
	class PhysicsComponent : public Component {
	public:
	private:
		/** Represents the parent's current velocity vector */
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
