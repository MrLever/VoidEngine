#pragma once
//STD Headers
#include <cmath>
#include <ostream>

//Library Headers

//Math Headers

namespace math {
	struct Vector2 {
		/** The vector's x-component */
		float X;
		
		/** The vector's y-component */
		float Y;

		/**
		 * Defualt Constructor
		 */
		Vector2();

		/**
		 * Constructor 
		 * @param x The vector's X value
		 */
		Vector2(float x);

		/**
		 * Constructor
		 * @param x The vector's X value
		 * @param y The vector's Y value
		 */
		Vector2(float x, float y);

		/**
		 * Computes the dot product of two 2D vectors
		 * @return the dot product
		 */
		float Dot(const Vector2& other) const;

		/**
		 * Equality comparison overload
		 */
		bool operator== (const Vector2& other) const;

		/**
		 * Non-member addition operator overload
		 */
		friend Vector2 operator+ (const Vector2& lhs, const Vector2& rhs);

		/**
		 * Non-member subtraction operator overload
		 */
		friend Vector2 operator- (const Vector2& lhs, const Vector2& rhs);

		/**
		 * Scalar multiplication operator overload
		 */
		friend Vector2 operator* (const Vector2& lhs, float rhs);

		/**
		 * Scalar multiplication operator overload
		 */
		friend Vector2 operator* (float lhs, const Vector2& rhs);
	};

	struct Vector3 {
		float X;
		float Y;
		float Z;

		/**
		 * Constructor
		 */
		Vector3();

		/**
		 * Constructor
		 */
		Vector3(float x);

		/**
		 * Constructor
		 */
		Vector3(float x, float y);
		
		/**
		 * Constructor
		 */
		Vector3(float x, float y, float z);

		/**
		 * Computes the dot product of two 3D vectors
		 * @return the dot product
		 */
		float Dot(const Vector3& other) const;

		/**
		 * Computes the cross product of two 3D vectors
		 * @return the perpendicular vector
		 */
		Vector3 Cross(const Vector3& other) const;

		/**
		 * Calculates the magnitude of this vector
		 * @return The magnitude
		 */
		float Magnitude() const;

		/**
		 * Calculates the magnitude of this vector
		 * @return The magnitude
		 */
		float Magnitude2() const;

		/**
		 * Non-destructive method to get this vector's unit vector
		 * @return the Unit Vector that corresponds to this vector
		 */
		[[nodiscard]] Vector3 Normalize() const;

		/**
		 * Equality comparison overload
		 */
		bool operator== (const Vector3& other);

		/**
		 * Addition assignment overload
		 */
		Vector3& operator+= (const Vector3& rhs);

		/**
		 * Non-member addition operator overload
		 */
		friend Vector3 operator+ (const Vector3& lhs, const Vector3& rhs);

		/**
		 * Subtraction assignment overload
		 */
		Vector3& operator-= (const Vector3& rhs);

		/**
		 * Non-member subtraction operator overload
		 */
		friend Vector3 operator- (const Vector3& lhs, const Vector3& rhs);

		/**
		 * Scalar multiplication assignment overload
		 */
		Vector3& operator*= (float rhs);

		/**
		 * Scalar multiplication operator overload
		 */
		friend Vector3 operator* (const Vector3& lhs, float rhs);

		/**
		 * Scalar multiplication operator overload
		 */
		friend Vector3 operator* (float lhs, const Vector3& rhs);

		/**
		 * Scalar division assignment overload
		 */
		Vector3& operator/= (float rhs);

		/**
		 * Scalar division operator overload
		 */
		friend Vector3 operator/ (const Vector3& lhs, float rhs);

		/**
		 * Scalar division operator overload
		 */
		friend Vector3 operator/ (float lhs, const Vector3& rhs);

		/**
		 * Output stream operator
		 */
		friend std::ostream& operator<< (std::ostream& out, const Vector3& vec);
	};

	struct Vector4 {
		float X;

		float Y;

		float Z;

		float W;

		/**
		 * Constructor
		 */
		Vector4();

		/**
		 * Constructor
		 */
		Vector4(float x);

		/**
		 * Constructor
		 */
		Vector4(float x, float y);

		/**
		 * Constructor
		 */
		Vector4(float x, float y, float z);

		/**
		 * Constructor
		 */
		Vector4(float x, float y, float z, float w);
	};

	using Color = Vector4;
}