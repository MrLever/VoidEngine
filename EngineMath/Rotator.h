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
		/** Rotation around the X axis*/
		float Roll;

		/** Rotation around the Y axis */
		float Pitch;
		
		/** Rotation around the Z axis */
		float Yaw;

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
		Rotator(float roll, float pitch, float yaw);

		/**
		 * Returns a direction vector that corresponds to this rotator
		 */
		Vector3 ToVector() const;

		/**
		 * Output stream operator overload
		 */
		friend std::ostream& operator<< (std::ostream& out, const Rotator& r);

		bool operator== (const Rotator& other) const;

	};

}
