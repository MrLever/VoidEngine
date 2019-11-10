//STD Headers

//Library Headers

//Void Engine Headers
#include "Rotator.h"
#include "Quaternion.h"

namespace math {
	Rotator::Rotator() : Yaw(0.0f), Pitch(0.0f), Roll(0.0f) {

	}

	Rotator::Rotator(float roll, float yaw, float pitch) {
		//Bound roll -360 -> 360 (exclusive)
		if (roll > 359) {
			roll = (float)std::fmod(roll, 360);
		}
		else if (roll < -359) {
			roll = (float)std::fmod(roll, -360);
		}

		//Bound yaw -360 -> 360 (exclusive)
		if (yaw > 359) {
			yaw = (float)std::fmod(yaw, 360);
		}
		else if (yaw < -359) {
			yaw = (float)std::fmod(yaw, -360);
		}

		//Bound pitch -360 -> 360 (exclusive)
		if (pitch > 359) {
			pitch = (float)std::fmod(pitch, 360);
		}
		else if (pitch < -359) {
			pitch = (float)std::fmod(pitch, -360);
		}

		Roll = roll;
		Yaw = yaw;
		Pitch = pitch;
	}

	Vector3 Rotator::ToVector() const {
		return Quaternion(*this).ToVector();
	}

	bool Rotator::operator==(const Rotator& other) const {
		constexpr float EPSILON = .1f;

		return
			((std::abs(Yaw - other.Yaw)) < EPSILON) &&
			((std::abs(Pitch - other.Pitch)) < EPSILON) &&
			((std::abs(Roll - other.Roll)) < EPSILON);
	}

	std::ostream& operator<<(std::ostream& out, const Rotator& r) {
		out << "rotation: [" << r.Yaw << ", " << r.Pitch << ", " << r.Roll << "]";
		return out;
	}
}
