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
			pitch = std::fmod(pitch, 360);
		}
		if (pitch < -359) {
			pitch = std::fmod(pitch, -360);
		}

		//Bound yaw -360 -> 360 (exclusive)
		if (yaw > 359) {
			yaw = std::fmod(yaw, 360);
		}
		if (pitch < -359) {
			yaw = std::fmod(yaw, -360);
		}

		//Bound roll -360 -> 360 (exclusive)
		if (roll > 359) {
			roll = std::fmod(roll, 360);
		}
		if (roll < -359) {
			roll = std::fmod(roll, -360);
		}

		Pitch = pitch;
		Yaw = yaw;
		Roll = roll;
	}
}
