//STD Headers

//Library Headers

//Void Engine Headers
#include "math/Rotator.h"
#include "math/Quaternion.h"

namespace math {
	Rotator::Rotator(float pitch, float yaw, float roll)
		: Pitch(pitch), Yaw(yaw), Roll(roll) {

	}

	Vector3 Rotator::AsVector() const {
		return Quaternion(*this).AsVector();
	}

	Quaternion Rotator::AsQuaternion() const {
		return Quaternion(*this);
	}

	Rotator& Rotator::Normalize() {
		Pitch = Clamp(Pitch);
		Yaw = Clamp(Yaw);
		Roll = Clamp(Roll);

		return *this;
	}

	Rotator Rotator::Normalize(const Rotator& rotator) {
		return Rotator(rotator).Normalize();
	}

	bool Rotator::operator==(const Rotator& other) const {
		return this->Equals(other);
	}

	bool Rotator::Equals(const Rotator& other, float epsilon) const {
		auto lhs = Quaternion(Normalize(*this));
		auto rhs = Quaternion(Normalize(other));

		return std::abs(lhs.Dot(rhs) - 1) <= epsilon;
	}

	Rotator Rotator::operator+(const Rotator& other) {
		return Rotator(
			Pitch + other.Pitch, 
			Roll + other.Roll, 
			Yaw + other.Yaw
		);
	}
	
	Rotator Rotator::operator-(const Rotator& other) {
		return Rotator(
			Pitch - other.Pitch, 
			Roll - other.Roll, 
			Yaw - other.Yaw
		);
	}

	Rotator operator*(const Rotator& lhs, float rhs) {
		return Rotator(
			lhs.Pitch * rhs, 
			lhs.Roll * rhs,
			lhs.Yaw * rhs
		);
	}

	Rotator operator*(float lhs, const Rotator& rhs) {
		return rhs * lhs;
	}

	std::ostream& operator<<(std::ostream& out, const Rotator& r) {
		out << "rotation: [" << r.Pitch << ", " << r.Roll << ", " << r.Yaw << "]";
		return out;
	}

	float Rotator::Clamp(float value) {
		value = (float)std::fmod(value, 360);
		return (value >= 0) ? value : value + 360.0f;
	}
}
