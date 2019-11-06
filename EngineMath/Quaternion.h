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
		 * Euler to Quaternion
		 */
		Quaternion(const Rotator& euler);

		/**
		 * Constructor
		 * Direct initialization
		 */
		Quaternion(float w, float x, float y, float z);

		/**
		 * Constructor
		 * Vector to rotation
		 */
		Quaternion(const Vector3& vec);

		/**
		 * Converts Quaternion to euler angles
		 */
		Rotator ToEuler() const;

		/**
		 * Returns the corresponding unit Quaternion
		 */
		Quaternion Normalize() const;

		/**
		 * Returns the Quaternion's magnitude
		 */
		float Magnitude() const;

		/**
		 * Applies the rotation represented by this 
		 * Quaternion to the supplied vector
		 */
		Vector3 Rotate(const Vector3& vec) const;
		
		/**
		 * Unary minus operator overload
		 */
		Quaternion operator- () const;

		/**
		 * Float division overload
		 */
		friend Quaternion operator/ (const Quaternion& quat, float val);

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

