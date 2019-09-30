//STD Headers

//Library Headers

//Void Engine Headers
#include "Rotator.h"

namespace EngineMath {
	Rotator::Rotator() : Pitch(0.0f), Yaw(0.0f), Roll(0.0f) {

	}

	Rotator::Rotator(float pitch, float yaw, float roll) {
		//Bound pitch -360 -> 360 (exclusive)
		if (pitch > 359) {
			pitch = (float)std::fmod(pitch, 360);
		}
		if (pitch < -359) {
			pitch = (float)std::fmod(pitch, -360);
		}

		//Bound yaw -360 -> 360 (exclusive)
		if (yaw > 359) {
			yaw = (float)std::fmod(yaw, 360);
		}
		if (pitch < -359) {
			yaw = (float)std::fmod(yaw, -360);
		}

		//Bound roll -360 -> 360 (exclusive)
		if (roll > 359) {
			roll = (float)std::fmod(roll, 360);
		}
		if (roll < -359) {
			roll = (float)std::fmod(roll, -360);
		}

		Pitch = pitch;
		Yaw = yaw;
		Roll = roll;
	}

	Vector3 Rotator::ToVector() const {
		//Convert to radians
		auto pitch = EngineMath::ToRadians(Pitch);
		auto yaw = EngineMath::ToRadians(Yaw);
		
		return Vector3(
			std::cos(pitch) * std::cos(yaw),
			std::sin(pitch),
			std::cos(pitch) * std::sin(yaw)
		).Normalize();
	}

	std::ostream& operator<<(std::ostream& out, const Rotator& r) {
		out << "rotation: [" << r.Pitch << ", " << r.Yaw << ", " << r.Roll << "]";
		return out;
	}
}
