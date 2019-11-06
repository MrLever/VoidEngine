//STD Headers

//Library Headers

//Void Engine Headers
#include "Quaternion.h"
#include "Rotator.h"
#include "MathConstants.h"

namespace math {
	Quaternion::Quaternion(const Rotator& euler) {
		/**
		 * Adapted from:
		 * https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
		 */
		float yawHalf = ToRadians(euler.Yaw * 0.5f);
		float pitchHalf = ToRadians(euler.Pitch * 0.5f);
		float rollHalf = ToRadians(euler.Roll * 0.5f);

		float cy = std::cosf(yawHalf);
		float sy = std::sinf(yawHalf);
		float cp = std::cosf(pitchHalf);
		float sp = std::sinf(pitchHalf);
		float cr = std::cosf(rollHalf);
		float sr = std::sinf(rollHalf);

		W = cy * cp * cr + sy * sp * sr;
		X = cy * cp * sr - sy * sp * cr;
		Y = sy * cp * sr + cy * sp * cr;
		Z = sy * cp * cr - cy * sp * sr;
	}

	Quaternion::Quaternion(float w, float x, float y, float z) 
		: W(w), X(x), Y(y), Z(z) {
	}
	
	Quaternion::Quaternion(const Vector3& vec) 
		: W(0.0f), X(vec.X), Y(vec.Y), Z(vec.Z) {

	}

	Rotator Quaternion::ToEuler() const {
		Rotator euler;

		euler.Roll = ToDegrees(
			std::atan2f(
				2.0f * ((W*X) + (Y*Z)),
				1.0f - (2.0f * ((X*X) + (Y*Y)))
			)
		);

		euler.Pitch = ToDegrees(
			std::asinf(
				2.0f * ((W * Y) - (X * Z))
			)
		);

		euler.Yaw = ToDegrees(
			std::atan2f(
				2.0f * ((W * Z) + (X * Y)),
				1.0f - (2.0f * ((Y * Y) + (Z * Z)))
			)
		);
		
		return euler;
	}

	Quaternion Quaternion::Normalize() const {
		return *this / Magnitude();
	}

	float Quaternion::Magnitude() const {
		return std::sqrtf(
			(X*X) + (Y*Y) + (Z*Z) + (W*W)
		);
	}

	Vector3 Quaternion::Rotate(const Vector3& vec) const {
		// Extract the vector part of the quaternion
		Vector3 u(X, Y, Z);

		auto t = 2.0f * u.Cross(vec);
		return vec + W * t + u.Cross(t);
	}

	Quaternion Quaternion::operator-() const {
		return Quaternion(-W, -X, -Y, -Z).Normalize();
	}

	bool Quaternion::IsValid() {
		return ((W*W) + (X*X) + (Y*Y) + (Z*Z) - 1) < std::numeric_limits<float>::epsilon();
	}

	Quaternion operator/(const Quaternion& quat, float val) {
		return Quaternion(quat.W / val, quat.X / val, quat.Y / val, quat.Z / val);
	}
}