#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Vector.h"

namespace math {

	struct Rotator;

	struct Quaternion {
		/**
		 * Constructor
		 */
		Quaternion(const Rotator& euler);

		/**
		 * Converts Quaternion to euler angles
		 */
		Rotator ToEuler() const;

		/**
		 * Allows user to query if a quaternion is valid
		 */
		bool IsValid();
	
		/** The four parameters needed to define a quaternion */
		float W;
		float X;
		float Y;
		float Z;
	};
}

