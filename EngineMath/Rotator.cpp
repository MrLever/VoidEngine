//STD Headers

//Library Headers

//Void Engine Headers
#include "Rotator.h"

namespace math {
	Rotator::Rotator() : Pitch(0.0f), Yaw(0.0f), Roll(0.0f) {

	}

	Rotator::Rotator(float roll, float pitch, float yaw) {
		//Bound roll -360 -> 360 (exclusive)
		if (roll > 359) {
			roll = (float)std::fmod(roll, 360);
		}
		else if (roll < -359) {
			roll = (float)std::fmod(roll, -360);
		}

		//Bound pitch -360 -> 360 (exclusive)
		if (pitch > 359) {
			pitch = (float)std::fmod(pitch, 360);
		}
		else if (pitch < -359) {
			pitch = (float)std::fmod(pitch, -360);
		}

		//Bound yaw -360 -> 360 (exclusive)
		if (yaw > 359) {
			yaw = (float)std::fmod(yaw, 360);
		}
		else if (pitch < -359) {
			yaw = (float)std::fmod(yaw, -360);
		}

		Pitch = pitch;
		Yaw = yaw;
		Roll = roll;
	}

	Vector3 Rotator::ToVector() const {
		//Convert to radians
		auto pitch = math::ToRadians(Pitch);
		auto yaw = math::ToRadians(Yaw);
		
		return Vector3(
			std::cos(pitch) * std::cos(yaw),
			std::sin(pitch),
			std::cos(pitch) * std::sin(yaw)
		).Normalize();
	}

	bool Rotator::operator==(const Rotator& other) const {
		constexpr float EPSILON = std::numeric_limits<float>::epsilon() * 100;

		return
			((std::abs(Pitch - other.Pitch)) < EPSILON) &&
			((std::abs(Yaw - other.Yaw)) < EPSILON) &&
			((std::abs(Roll - other.Roll)) < EPSILON);
	}

	std::ostream& operator<<(std::ostream& out, const Rotator& r) {
		out << "rotation: [" << r.Pitch << ", " << r.Yaw << ", " << r.Roll << "]";
		return out;
	}
}
