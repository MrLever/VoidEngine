//STD Headers

//Library Headers

//Void Engine Headers
#include "math/Quaternion.h"
#include "math/Rotator.h"
#include "math/MathConstants.h"

namespace math {

	Quaternion::Quaternion() {
		W = 1;
		X = Y = Z = 0;
	}
		
	Quaternion::Quaternion(const Rotator& euler) {
		float alphaHalf = ToRadians(euler.Roll) / 2;
		float betaHalf = ToRadians(euler.Pitch) / 2;
		float gammaHalf = ToRadians(euler.Yaw) / 2;
		
		W = std::cosf(alphaHalf) * std::cosf(betaHalf) * std::cosf(gammaHalf) +
			std::sinf(alphaHalf) * std::sinf(betaHalf) * std::sinf(gammaHalf);

		X = std::sinf(alphaHalf) * std::cosf(betaHalf) * std::cosf(gammaHalf) -
			std::cosf(alphaHalf) * std::sinf(betaHalf) * std::sinf(gammaHalf);

		Y = std::cosf(alphaHalf) * std::sinf(betaHalf) * std::cosf(gammaHalf) +
			std::sinf(alphaHalf) * std::cosf(betaHalf) * std::sinf(gammaHalf);

		Z = std::cosf(alphaHalf) * std::cosf(betaHalf) * std::sinf(gammaHalf) -
			std::sinf(alphaHalf) * std::sinf(betaHalf) * std::cosf(gammaHalf);
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

	Vector3 Quaternion::ToVector() const {
		return Rotate(Vector3(1, 0, 0));
	}

	Quaternion& Quaternion::Normalize() {
		auto mag = Magnitude();
		W /= mag;
		X /= mag;
		Y /= mag;
		Z /= mag;

		return *this;
	}

	Quaternion Quaternion::Normalize(const Quaternion& quat) {
		return Quaternion(quat).Normalize();
	}

	float Quaternion::Magnitude() const {
		return std::sqrtf(
			(X*X) + (Y*Y) + (Z*Z) + (W*W)
		);
	}

	Vector3 Quaternion::Rotate(const Vector3& vec) const {
		Quaternion q(*this);
		q.Normalize();

		// Extract the vector part of the quaternion
		Vector3 u(q.X, q.Y, q.Z);

		auto t = 2.0f * u.Cross(vec);
		return vec + q.W * t + u.Cross(t);
	}

	Quaternion Quaternion::operator-() const {
		return Quaternion(-W, -X, -Y, -Z).Normalize();
	}

	bool Quaternion::IsValid() {
		return ((W*W) + (X*X) + (Y*Y) + (Z*Z) - 1) < std::numeric_limits<float>::epsilon();
	}

	Quaternion operator/ (const Quaternion& quat, float val) {
		return Quaternion(quat.W / val, quat.X / val, quat.Y / val, quat.Z / val);
	}

	Quaternion operator* (const Quaternion& lhs, const Quaternion& rhs) {
		return 
			Quaternion(
				lhs.W * rhs.W - lhs.X * rhs.X - lhs.Y * rhs.Y - lhs.Z * rhs.Z,
				lhs.W * rhs.X + lhs.X * rhs.W + lhs.Y * rhs.Z - lhs.Z * rhs.Y,
				lhs.W * rhs.Y - lhs.X * rhs.Z + lhs.Y * rhs.W + lhs.Z * rhs.X,
				lhs.W * rhs.Z + lhs.X * rhs.Y - lhs.Y * rhs.X + lhs.Z * rhs.W
			);
	}

	bool Quaternion::operator==(const Quaternion& other) const {
		return this->Equals(other, DEFUALT_FLOAT_EPSILON);
	}

	bool Quaternion::Equals(const Quaternion& other, float epsilon) const {
		return std::abs(this->Dot(other)) - 1 < epsilon;
	}

	float Quaternion::Dot(const Quaternion& other) const {
		return (W * other.W) + (X * other.X) + (Y * other.Y) + (Z * other.Z);
	}
}