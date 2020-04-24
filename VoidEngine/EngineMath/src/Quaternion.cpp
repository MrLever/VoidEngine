//STD Headers

//Library Headers

//Void Engine Headers
#include "math/Quaternion.h"
#include "math/Rotator.h"
#include "math/MathUtils.h"

namespace math {

	Quaternion Quaternion::Identity = Quaternion(1, 0, 0, 0);

	Quaternion::Quaternion() {
		W = 1;
		X = Y = Z = 0;
	}
		
	Quaternion::Quaternion(const Rotator& euler) {
		float alphaHalf = ToRadians(euler.Pitch) / 2;
		float betaHalf = ToRadians(euler.Yaw) / 2;
		float gammaHalf = ToRadians(euler.Roll) / 2;
		
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

	Rotator Quaternion::AsEuler() const {
		Rotator euler;
		
		auto rollRadians =
			std::atan2f(
				2.0f * ((W * X) + (Y * Z)),
				1.0f - (2.0f * ((X * X) + (Y * Y)))
			);

		//Restrict pitch to avoid gimbal lock math errors
		auto sinPart = 2 * (W * Y - Z * X);
		float pitchRadians;
		if (std::abs(sinPart) >= 1) {
			pitchRadians = std::copysignf((float)PI / 2, sinPart);
		}
		else {
			pitchRadians = std::asin(sinPart);
		}

		auto yawRadians =
			std::atan2f(
				2.0f * ((W * Z) + (X * Y)),
				1.0f - (2.0f * ((Y * Y) + (Z * Z)))
			);

		euler.Pitch = ToDegrees(rollRadians);

		euler.Yaw = ToDegrees(pitchRadians);
			
		euler.Roll = ToDegrees(yawRadians);
		
		return euler;
	}

	Vector3 Quaternion::AsVector() const {
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

	Quaternion Quaternion::Inverse() const {
		return Quaternion(W, -X, -Y, -Z) / MagnitudeSqr();
	}

	void Quaternion::Invert() {
		X = -X;
		Y = -Y;
		Z = -Z;
	}

	float Quaternion::Magnitude() const {
		return std::sqrtf(
			(X*X) + (Y*Y) + (Z*Z) + (W*W)
		);
	}

	float Quaternion::MagnitudeSqr() const {
		return (X * X) + (Y * Y) + (Z * Z) + (W * W);
	}

	Vector3 Quaternion::Rotate(const Vector3& vec) const {
		Quaternion q(*this);
		Quaternion p(0, vec.X, vec.Y, vec.Z);
		Quaternion qPrime(q.Inverse());

		auto res = q * p * qPrime;

		return Vector3(res.X, res.Y, res.Z);
	}

	Quaternion& Quaternion::operator= (const Quaternion& other) {
		W = other.W;
		X = other.X;
		Y = other.Y;
		Z = other.Z;

		return *this;
	}

	Quaternion Quaternion::operator- () const {
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

	Quaternion& Quaternion::operator*=(const Quaternion& other) {
		W = W * other.W - X * other.X - Y * other.Y - Z * other.Z;
		X =	W * other.X + X * other.W + Y * other.Z - Z * other.Y;
		Y =	W * other.Y - X * other.Z + Y * other.W + Z * other.X;
		Z =	W * other.Z + X * other.Y - Y * other.X + Z * other.W;

		return *this;
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