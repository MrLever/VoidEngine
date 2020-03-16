#include "..\..\include\core\gameplay_framework\Transform.h"
//STD Headers

//Library headers

//Void Engine Headers

namespace core {
	Transform::Transform()
		: m_LocalPosition(0, 0, 0),
		  m_LocalRotation(),
		  m_LocalScale(1, 1, 1),
		  m_Parent(nullptr) {

	}

	Transform::Transform(
		const math::Vector3& pos, const math::Quaternion& rot, 
		const math::Vector3& scale, Transform* parent) 
		: m_LocalPosition(pos),
		  m_LocalRotation(rot),
		  m_LocalScale(scale),
		  m_Parent(parent) {

	}

	Transform::Transform(const math::Vector3& pos, Transform* parent) 
		: m_LocalPosition(pos), 
		  m_LocalRotation(), 
		  m_LocalScale(1,1,1), 
		  m_Parent(parent) {
	}

	Transform::Transform(const math::Quaternion& rot, Transform* parent) 
		: m_LocalPosition(0,0,0),
	      m_LocalRotation(rot), 
	      m_LocalScale(1,1,1),
		  m_Parent(parent) {

	}

	Transform::Transform(const math::Vector3& pos, const math::Quaternion& rot, Transform* parent) 
		: m_LocalPosition(pos),
		  m_LocalRotation(rot),
		  m_LocalScale(1, 1, 1),
		  m_Parent(parent) {
	}

	math::Vector3 Transform::GetLocalPosition() const {
		return m_LocalPosition;
	}

	void Transform::SetLocalPosition(const math::Vector3& value) {
		m_LocalPosition = value;
	}

	math::Vector3 Transform::GetPosition() const {
		return (m_Parent == nullptr) ?
			m_LocalPosition :
			m_Parent->GetPosition() + m_LocalPosition;
	}

	void Transform::SetPosition(const math::Vector3& value) {
		if (m_Parent == nullptr) {
			m_LocalPosition = value;
		}
		else {
			m_LocalPosition = value - m_Parent->GetPosition();
		}
	}
	math::Quaternion Transform::GetLocalRotation() const {
		return m_LocalRotation;
	}

	void Transform::SetLocalRotation(const math::Quaternion& value) {
		m_LocalRotation = value;
	}

	math::Quaternion Transform::GetRotation() const {
		return (m_Parent == nullptr) ?
			m_LocalRotation :
			m_Parent->GetRotation() * m_LocalRotation;
	}

	void Transform::SetRotation(const math::Quaternion& value) {
		m_LocalRotation = value;
	}

	math::Vector3 Transform::GetLocalScale() const {
		return m_LocalScale;
	}

	void Transform::SetLocalScale(const math::Vector3& value) {
		m_LocalScale = value;
	}

	math::Vector3 Transform::GetScale() const {
		return (m_Parent == nullptr) ?
			m_LocalScale :
			m_Parent->GetScale() + m_LocalScale;
	}

	void Transform::SetScale(const math::Vector3& value) {
		m_LocalScale = (m_Parent == nullptr) ?
			value :
			value - m_Parent->GetScale();
	}
}