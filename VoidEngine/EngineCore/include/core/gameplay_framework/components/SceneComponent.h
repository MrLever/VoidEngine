#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/gameplay_framework/Component.h"
#include "core/gameplay_framework/Transform.h"

namespace core {
	/**
	 * @class SceneComponent
	 * @brief Required by all entities, SceneComponents are used in the Scene Graph to build a tree of all entities
	 */
	class SceneComponent : public Component {
		/**
		 * Declare custom RTTI support
		 */
		TYPE_INFO_DECL(SceneComponent)

	public:
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
		SceneComponent* m_Parent;
		std::vector<SceneComponent*> m_Children;
		
		Transform m_Transform;
	};
}