#pragma once
//STD Headers

//Library headers

//Void Engine Headers
#include "math/Vector.h"
#include "math/Rotator.h"
#include "math/Quaternion.h"

namespace core {
	struct Transform {
	private:
		/** Transform world position data */
		math::Vector3 _localPosition;

		/** Transform rotation data */
		math::Quaternion _localRotation;

		/** Transform scale data */
		math::Vector3 _localScale;

	public:
		/** 
		 * World Position property accessors
		 */
		math::Vector3 Position() const { 
			auto parentPos = (Parent == nullptr) ? math::Vector3() : Parent->Position();
			return parentPos + _localPosition;
		}
		void Position(const math::Vector3& value) { 
			//UPDATE HIERARCHY
		}

		/**
		 * Local Position property accessors
		 */
		math::Vector3 LocalPosition() const { return _localPosition; }
		void LocalPosition(const math::Vector3& value) {
			//UPDATE HIERARCHY
		}
		
		/** 
		 * World rotation property accessors 
		 */
		math::Quaternion Rotation() { 
			auto parentRotation = (Parent == nullptr) ? math::Quaternion() : Parent->Rotation();
			return parentRotation * _localRotation;
		};
		void Rotation(const math::Quaternion& value) { 
			//UPDATE HIERARCHY 
		}

		/** 
		 * Local rotation property accessors 
		 */
		math::Quaternion LocalRotation() { return _localRotation; };
		void LocalRotation(const math::Quaternion& value) { 
			//UPDATE HIERARCHY 
		}


		/** 
		 * Local scale property accessors 
		 */
		math::Vector3 Scale() { return _localScale; };
		void Scale(const math::Vector3& value) {
			//UPDATE HIERARCHY
		}

		/**
		 * Constructor
		 */
		Transform() 
			: _localPosition(0,0,0), 
			  _localRotation(),
			  _localScale(1,1,1),
			  Parent(nullptr) {

		}

		/**
		 * Constructor
		 */
		Transform(math::Vector3 pos, math::Quaternion rot, math::Vector3 scale) 
			: _localPosition(pos),
			  _localRotation(),
			  _localScale(scale),
			  Parent(nullptr) {
		}

		/**
		 * Constructor
		 */
		Transform(const Transform* parent, math::Vector3 pos, math::Quaternion rot, math::Vector3 scale)
			: _localPosition(pos),
			_localRotation(),
			_localScale(scale),
			Parent(parent) {

		}

		/**
		 * Copy Constructor
		 */
		Transform(Transform&) = delete;

	private:
		const Transform* Parent;
	};
}