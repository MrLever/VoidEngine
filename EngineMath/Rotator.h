#pragma once
//STD Headers
#include <cmath>
#include <ostream>

//Library Headers

//Void Engine Headers
#include "Vector.h"
#include "MathConstants.h"

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

		/** Rotation around the Z axis*/
		float Roll;

		/**
		 * Constructor
		 */
		Rotator();

		/**
		 * Constructor
		 * @param pitch The rotator's pitch
		 * @param yaw The rotator's yaw
		 * @param roll The rotator's roll
		 */
		Rotator(float pitch, float yaw, float roll);

		/**
		 * Returns a direction vector that corresponds to this rotator
		 */
		Vector3 ToVector() const;

		/**
		 * Output stream operator overload
		 */
		friend std::ostream& operator<< (std::ostream& out, const Rotator& r);

	};

}
