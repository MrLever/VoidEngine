#pragma once

#include "Vector3D.h"

namespace EngineMath {

	template <typename T, int count>
	class Vector {

	public:
		//CTORS
		/**
		* Default Constructor
		*/
		Vector();

		/**
		* Default Constructor
		* @param values The variadic set of values to fill the void
		*/
		template <typename... Ts> Vector(Ts... values);

		//Public Member Functions
		//NOTE: Most of these will be changed to 
		/**
		* Calculates the sum of two Vectors
		* @param other Other vector to sum
		* @return Vector of the sum
		*/
		Vector Sum(Vector other);

		/**
		* Subtracts two Vectors
		* @param other Other vector to subtract from original
		* @return Vector of the sum
		*/
		Vector Subtract(Vector other);

		/**
		* Permits the scalar action upon the Vector class
		* @param scalar The scalar from the valid field
		* @return Vector of the scaled action
		*/
		Vector Scalar(T scalar);

		/**
		* Dot products two vectors
		* @param other Other vector to dot product
		* @return Scalar resultant
		*/
		auto Dot(Vector other);

		/**
		* Cross products two vectors. 
		* @param other Other vector to cross product
		* @return Vector resultant
		*/
		Vector Cross(Vector other);

		//static Vector Interpolate(T xa, T ya, T za, T wa, T xb, T yb, T zb, T wb);

		/**
		* Projects onto the secondary vector
		* @param other Other vector to project onto
		* @return Vector resultant
		*/
		Vector Project(Vector other);
	};
}