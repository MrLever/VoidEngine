#pragma once
//STD Headers

//Library headers

//Void Engine Headers
#include "math/Vector.h"
#include "math/Rotator.h"
#include "math/Quaternion.h"

namespace core {
	struct Transform {
		/** The entity's position in 3D space */
		math::Vector3 Position;

		/** The entity's rotation in 3D space */
		math::Quaternion Rotation;

		/** The entity's scale in 3D space */
		math::Vector3 Scale;

		/**
		 * Constructor
		 */
		Transform() : Position(0,0,0), Rotation(), Scale(1,1,1) {
		
		}

		/**
		 * Constructor
		 */
		inline Transform(math::Vector3 pos, math::Quaternion rot, math::Vector3 scale) 
			: Position(pos), Rotation(rot), Scale(scale) {
			
		}
	};
}