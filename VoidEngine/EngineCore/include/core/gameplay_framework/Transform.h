#pragma once
//STD Headers
#include <vector>

//Library headers

//Void Engine Headers
#include "math/Vector.h"
#include "math/Rotator.h"
#include "math/Quaternion.h"

namespace core {
	class Entity;

	class Transform {
	public:

		/**
		 * Constructor
		 */
		Transform(Entity& owner);

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
			const math::Vector3& scale,
			Entity& owner
		);

		/**
		 * Constructor
		 * @param pos The local position of the transform relative to parent
		 * @param parent The parent of the transform being constructed
		 */
		Transform(const math::Vector3& pos, Entity& owner);

		/**
		 * Constructor
		 * @param rot The local rotation of the transform relative to parent
		 * @param parent The parent of the transform being constructed
		 */
		Transform(const math::Quaternion& pos, Entity& owner);

		/**
		 * Constructor
		 * @param pos The local position of the transform relative to parent
		 * @param rot The local rotation of the transform relative to the parent
		 * @param parent The parent of the transform being constructed
		 */
		Transform(
			const math::Vector3& pos,
			const math::Quaternion& rot,
			Entity& owner
		);

		/**
		 * Copy Constructor
		 */
		Transform(Transform&) = delete;

		/**
		 * Copy Constructor
		 */
		Transform& operator= (const Transform&) = delete;

		/**
		 * Local position getter
		 * @return The object's position relative to it's parent
		 */
		math::Vector3 GetLocalPosition() const;

		/**
		 * Local position setter
		 * @param value The new position of the object in local space
		 */
		void SetLocalPosition(const math::Vector3& value);

		/**
		 * World position getter
		 * @return The object's position in world space
		 */
		math::Vector3 GetPosition() const;

		/**
		 * World position getter
		 * @return The object's position in world space
		 */
		void SetPosition(const math::Vector3& value);

		/**
		 * Local position getter
		 * @return The object's position relative to it's parent
		 */
		math::Quaternion GetLocalRotation() const;

		/**
		 * Local position setter
		 * @param value The new position of the object in local space
		 */
		void SetLocalRotation(const math::Quaternion& value);

		/**
		 * World position getter
		 * @return The object's position in world space
		 */
		math::Quaternion GetRotation() const;

		/**
		 * World position getter
		 * @return The object's position in world space
		 */
		void SetRotation(const math::Quaternion& value);

		/**
		 * Local position getter
		 * @return The object's position relative to it's parent
		 */
		math::Vector3 GetLocalScale() const;

		/**
		 * Local position setter
		 * @param value The new position of the object in local space
		 */
		void SetLocalScale(const math::Vector3& value);

		/**
		 * World position getter
		 * @return The object's position in world space
		 */
		math::Vector3 GetScale() const;

		/**
		 * World position getter
		 * @return The object's position in world space
		 */
		void SetScale(const math::Vector3& value);

		/**
		 * Gets the transform's local "forward" direction in world space
		 */
		math::Vector3 GetForward() const;

		/**
		 * Gets the transform's local "up" direction in world space
		 */
		math::Vector3 GetUp() const;

	private:
		inline Transform* Parent() const;

		Entity& m_Entity;

		math::Vector3 m_LocalPosition;
		math::Quaternion m_LocalRotation;
		math::Vector3 m_LocalScale;
	};
}