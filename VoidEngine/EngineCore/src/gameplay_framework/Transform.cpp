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
		if (m_Parent == nullptr) {
			return m_LocalPosition;
		}
		else {
			auto parentPos = m_Parent->GetPosition();
			auto parentRotation = m_Parent->GetRotation();
			auto positionInParentSpace = parentRotation.Rotate(m_LocalPosition);
			return parentPos + positionInParentSpace;
		}
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
		if (m_Parent == nullptr) {
			m_LocalRotation = value;
		}
		else {
			m_LocalRotation = value * m_Parent->GetRotation().Inverse();
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
		m_LocalScale = (m_Parent == nullptr) ?
			value :
			value - m_Parent->GetScale();
	}
	
	void Transform::SetParent(Transform* parent) {
		//Preserve world position during parent transfer
		auto currentWorld = GetPosition();
		m_Parent = parent;
		SetPosition(currentWorld);
	}

	math::Vector3 Transform::GetForward() const {
		auto rotation = GetRotation().Normalize();
		return rotation.Rotate(math::Vector3::Forward);
	}

	math::Vector3 Transform::GetUp() const {
		auto rotation = GetRotation().Normalize();
		return rotation.Rotate(math::Vector3::Up);
	}

	void Transform::AddChild(Transform* child) {
		m_Children.push_back(child);
	}
}