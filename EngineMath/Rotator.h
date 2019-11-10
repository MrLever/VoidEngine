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
		float Roll;

		/** Rotation around the Y axis */
		float Yaw;
		
		/** Rotation around the Z axis */
		float Pitch;

		/**
		 * Constructor
		 */
		Rotator();

		/**
		 * Constructor
		 * @param roll The rotator's rotation around the X axis
		 * @param pitch The rotator's rotation around the y axis
		 * @param yaw The rotator's rotation around the z axis
		 */
		Rotator(float roll, float yaw, float pitch);

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
