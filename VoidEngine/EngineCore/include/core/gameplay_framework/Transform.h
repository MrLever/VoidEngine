#pragma once
//STD Headers

//Library headers

//Void Engine Headers
#include "math/Vector.h"
#include "math/Rotator.h"
#include "math/Quaternion.h"

namespace core {
	struct Transform {

	public:
		/** Transform world position data */
		math::Vector3 Position;

		/** Transform rotation data */
		math::Quaternion Rotation;

		/** Transform scale data */
		math::Vector3 Scale;

		/**
		 * Constructor
		 */
		Transform() 
			: Position(0,0,0), 
			  Rotation(),
			  Scale(1,1,1),
			  Parent(nullptr) {

		}

		/**
		 * Constructor
		 */
		Transform(math::Vector3 pos, math::Quaternion rot, math::Vector3 scale) 
			: Position(pos),
			  Rotation(),
			  Scale(scale),
			  Parent(nullptr) {
		}

		/**
		 * Constructor
		 */
		Transform(Transform* parent, math::Vector3 pos, math::Quaternion rot, math::Vector3 scale)
			: Position(pos),
			  Rotation(),
			  Scale(scale),
			  Parent(parent) {

		}

		/**
		 * Copy Constructor
		 */
		Transform(Transform&) = delete;

	private:
		Transform* Parent;
	};
}