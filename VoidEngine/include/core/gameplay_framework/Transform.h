#pragma once
//STD Headers
#include <vector>

//Library headers

//Void Engine Headers
#include "math/Vector.h"
#include "math/Rotator.h"
#include "math/Quaternion.h"

namespace core {
	struct Transform {
		math::Vector3 position;
		math::Quaternion rotation;
		math::Vector3 scale;

		/**
		 * Constructor
		 */
		Transform();

		/**
		 * Constructor
		 * @param pos The local position of the transform relative to parent
		 * @param rot The local rotation of the transform relative to the parent
		 * @param scale The local scale of the transform relative to the parent
		 * @param parent The parent of the transform being constructed
		 */
		Transform(
			const math::Vector3& pos,
			const math::Quaternion& rot,
			const math::Vector3& scale
		);

		/**
		 * Constructor
		 * @param pos The local position of the transform relative to parent
		 * @param parent The parent of the transform being constructed
		 */
		Transform(const math::Vector3& pos);

		/**
		 * Constructor
		 * @param rot The local rotation of the transform relative to parent
		 * @param parent The parent of the transform being constructed
		 */
		Transform(const math::Quaternion& pos);

		/**
		 * Constructor
		 * @param pos The local position of the transform relative to parent
		 * @param rot The local rotation of the transform relative to the parent
		 * @param parent The parent of the transform being constructed
		 */
		Transform(
			const math::Vector3& pos,
			const math::Quaternion& rot
		);
	};
}