//STD Headers

//Library Headers

//Void Engine Headers
#include "math/Rotator.h"
#include "math/Quaternion.h"

namespace math {
	Rotator::Rotator(float roll, float pitch, float yaw) 
		: Roll(roll), Pitch(pitch), Yaw(yaw) {

	}

	Vector3 Rotator::ToVector() const {
		return Quaternion(*this).ToVector();
	}

	Rotator& Rotator::Normalize() {
		Roll = Clamp(Roll);
		Pitch = Clamp(Pitch);
		Yaw = Clamp(Yaw);

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
			Roll + other.Roll, 
			Yaw + other.Yaw, 
			Pitch + other.Pitch
		);
	}
	
	Rotator Rotator::operator-(const Rotator& other) {
		return Rotator(
			Roll - other.Roll, 
			Yaw - other.Yaw, 
			Pitch - other.Pitch
		);
	}

	Rotator operator*(const Rotator& lhs, float rhs) {
		return Rotator(
			lhs.Roll * rhs, 
			lhs.Yaw * rhs,
			lhs.Pitch * rhs
		);
	}

	Rotator operator*(float lhs, const Rotator& rhs) {
		return rhs * lhs;
	}

	std::ostream& operator<<(std::ostream& out, const Rotator& r) {
		out << "rotation: [" << r.Roll << ", " << r.Yaw << ", " << r.Pitch << "]";
		return out;
	}

	float Rotator::Clamp(float value) {
		value = (float)std::fmod(value, 360);
		return (value >= 0) ? value : value + 360.0f;
	}
}
