#pragma once
//STD Headers
#include <cmath>
#include <ostream>

//Library Headers

//Void Engine Headers
#include "Vector.h"
#include "MathUtils.h"

namespace math {
	/**
	 * @class Rotator
	 * @brief Struct to encapsulate rotation information as euler angels
	 */
	struct Rotator {
		/** Rotation around the X axis */
		float Pitch;

		/** Rotation around the Y axis */
		float Yaw;

		/** Rotation around the Z axis */
		float Roll;		

		/**
		 * Constructor
		 * @param pitch The rotator's rotation around the x axis
		 * @param yaw The rotator's rotation around the y axis
		 * @param roll The rotator's rotation around the z axis
		 */
		Rotator(float pitch = 0.0f, float yaw = 0.0f, float roll = 0.0f);

		/**
		 * Copy Constructor
		 */
		Rotator(const Rotator& other) = default;

		/**
		 * Returns a unit direction vector that corresponds to this rotator
		 */
		[[nodiscard]] Vector3 AsVector() const;

		/**
		 * @return this euler angle as a quaternion
		 */
		[[nodiscard]] Quaternion AsQuaternion() const;

		/**
		 * Unwinds Rotator (clamps all values to 0 - 360)
		 */
		Rotator& Normalize();

		/**
		 * Non-destructively unwinds rotator
		 * @param rotator The rotation to normalize
		 */
		[[nodiscard]] static Rotator Normalize(const Rotator& rotator);

		/**
		 * Equality comparison operator
		 */
		bool operator== (const Rotator& other) const;

		/**
		 * Custom-epsilon equality comparison
		 * @param epsilon The per angle tolerance for equality
		 */
		bool Equals(const Rotator& other, float epsilon = DEFUALT_FLOAT_EPSILON) const;

		/**
		 * Non-member addition operator overload
		 */
		Rotator operator+ (const Rotator& other);

		/**
		 * Non-member subtraction operator overload
		 */
		Rotator operator- (const Rotator& other);

		/**
		 * Scalar multiplication operator overload
		 */
		friend Rotator operator* (const Rotator& lhs, float rhs);

		/**
		 * Scalar multiplication operator overload
		 */
		friend Rotator operator* (float lhs, const Rotator& rhs);
		
		/**
		 * Output stream operator overload
		 */
		friend std::ostream& operator<< (std::ostream& out, const Rotator& r);
	private:
		/**
		 * Clamps value of angle 0 - 360
		 */
		static float Clamp(float value);

	};

}
