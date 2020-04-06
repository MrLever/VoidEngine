//STD Headers

//Library headers

//Void Engine Headers
#include "core/gameplay_framework/Transform.h"
#include "core/gameplay_framework/Entity.h"

namespace core {
	Transform::Transform(Entity& owner)
		: m_LocalPosition(0, 0, 0),
		  m_LocalRotation(),
		  m_LocalScale(1, 1, 1),
		  m_Entity(owner) {

	}

	Transform::Transform(
		const math::Vector3& pos, const math::Quaternion& rot, 
		const math::Vector3& scale, Entity& owner)
		: m_LocalPosition(pos),
		  m_LocalRotation(rot),
		  m_LocalScale(scale),
		  m_Entity(owner) {

	}

	Transform::Transform(const math::Vector3& pos, Entity& owner)
		: m_LocalPosition(pos), 
		  m_LocalRotation(), 
		  m_LocalScale(1,1,1), 
		  m_Entity(owner) {
	}

	Transform::Transform(const math::Quaternion& rot, Entity& owner)
		: m_LocalPosition(0,0,0),
	      m_LocalRotation(rot), 
	      m_LocalScale(1,1,1),
		  m_Entity(owner) {

	}

	Transform::Transform(const math::Vector3& pos, const math::Quaternion& rot, Entity& owner)
		: m_LocalPosition(pos),
		  m_LocalRotation(rot),
		  m_LocalScale(1, 1, 1),
		  m_Entity(owner) {
	}

	math::Vector3 Transform::GetLocalPosition() const {
		return m_LocalPosition;
	}

	void Transform::SetLocalPosition(const math::Vector3& value) {
		m_LocalPosition = value;
	}

	math::Vector3 Transform::GetPosition() const {
		if (Parent() == nullptr) {
			return m_LocalPosition;
		}
		else {
			auto parentPos = Parent()->GetPosition();
			auto parentRotation = Parent()->GetRotation();
			auto positionInParentSpace = parentRotation.Rotate(m_LocalPosition);
			return parentPos + positionInParentSpace;
		}
	}

	void Transform::SetPosition(const math::Vector3& value) {
		if (Parent() == nullptr) {
			m_LocalPosition = value;
		}
		else {
			m_LocalPosition = value - Parent()->GetPosition();
		}
	}
	math::Quaternion Transform::GetLocalRotation() const {
		return m_LocalRotation;
	}

	void Transform::SetLocalRotation(const math::Quaternion& value) {
		m_LocalRotation = value;
	}

	math::Quaternion Transform::GetRotation() const {
		return (Parent() == nullptr) ?
			m_LocalRotation :
			Parent()->GetRotation() * m_LocalRotation;
		return m_LocalRotation;
	}

	void Transform::SetRotation(const math::Quaternion& value) {
		if (Parent() == nullptr) {
			m_LocalRotation = value;
		}
		else {
			m_LocalRotation = value * Parent()->GetRotation().Inverse();
		}
	}

	math::Vector3 Transform::GetLocalScale() const {
		return m_LocalScale;
	}

	void Transform::SetLocalScale(const math::Vector3& value) {
		m_LocalScale = value;
	}

	math::Vector3 Transform::GetScale() const {
		return m_LocalScale;
	}

	void Transform::SetScale(const math::Vector3& value) {
		m_LocalScale = (Parent() == nullptr) ?
			value :
			value - Parent()->GetScale();
	}

	math::Vector3 Transform::GetForward() const {
		auto rotation = GetRotation().Normalize();
		return rotation.Rotate(math::Vector3::Forward);
	}

	math::Vector3 Transform::GetUp() const {
		auto rotation = GetRotation().Normalize();
		return rotation.Rotate(math::Vector3::Up);
	}

	inline Transform* Transform::Parent() const {
		return (m_Entity.GetParent() != nullptr) ?
			&m_Entity.GetParent()->m_Transform :
			nullptr;
	}
}