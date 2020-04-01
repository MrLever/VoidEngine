#pragma once
//STD Headers
#include <initializer_list>

//Library Headers

//Void Engine Headers
#include "Vector.h"

namespace math {

	struct Rotator;

	struct Quaternion {
		static Quaternion Identity;
		
		/** The four parameters needed to define a quaternion */
		float W;
		float X;
		float Y;
		float Z;

		/**
		 * Constructor
		 */
		Quaternion();

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
		 * Converts Quaternion to euler angles
		 */
		Rotator ToEuler() const;

		/**
		 * Converts Quaternion to direction vector
		 */
		Vector3 ToVector() const;

		/**
		 * Destructively normalize quaternion
		 * @return reference to this quaternion
		 */
		Quaternion& Normalize();

		/**
		 * Non-destructively normalizes supplied quaternion
		 * @param quat The quaternion to normalize
		 * @return Unit quaternion corresponding to quat
		 */
		[[nodiscard]] static Quaternion Normalize(const Quaternion& quat);

		/**
		 * Returns inverse of this quaternion
		 * @return Unit quaternion that represents a rotation in the opposite direction		
		 */
		[[nodiscard]] Quaternion Inverse() const;

		/**
		 * Inverts this quaternion
		 * @return Unit quaternion that represents a rotation in the opposite direction
		 */
		void Invert();

		/**
		 * Returns the Quaternion's magnitude
		 */
		float Magnitude() const;

		/**
		 * Returns the Quaternion's squared magnitude
		 */
		float MagnitudeSqr() const;

		/**
		 * Applies the rotation represented by this 
		 * Quaternion to the supplied vector
		 * @Note: Operation will used normalized quaternion to apply rotation 
		 */
		Vector3 Rotate(const Vector3& vec) const;

		/**
		 * Assignment operator
		 */
		Quaternion& operator= (const Quaternion& other);

		/**
		 * Unary minus operator overload
		 */
		Quaternion operator- () const;

		/**
		 * Multiplication assignment operator
		 */
		Quaternion& operator*= (const Quaternion& other);

		/**
		 * Float division overload
		 */
		friend Quaternion operator/ (const Quaternion& quat, float val);

		/**
		 * Quaternion multiplication overload
		 */
		friend Quaternion operator* (const Quaternion& lhs, const Quaternion& rhs);

		/**
		 * Equality comparision operator
		 */
		bool operator== (const Quaternion& other) const;

		/**
		 * Custom epsilon equality comparison
		 * @param epsilon The margin of error for equality
		 */
		bool Equals(const Quaternion& other, float epsilon = DEFUALT_FLOAT_EPSILON) const;

		/**
		 * Computes the dot product of two Quaternions
		 * @return the dot product 
		 *         (which is the shortest angle between the axes of rotation of the quaternions)
		 */
		float Dot(const Quaternion& other) const;

		/**
		 * Allows user to query if a quaternion is valid
		 */
		bool IsValid();
	};
}

