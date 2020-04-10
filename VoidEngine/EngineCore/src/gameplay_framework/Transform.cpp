//STD Headers

//Library headers

//Void Engine Headers
#include "core/gameplay_framework/Transform.h"
#include "core/gameplay_framework/Entity.h"

namespace core {



	Transform::Transform() 
		: position(0, 0, 0),
		  rotation(),
		  scale(1, 1, 1) {
	
	}


	Transform::Transform(const math::Vector3& pos, const math::Quaternion& rot, const math::Vector3& scale) 
		: position(pos),
		  rotation(rot),
		  scale(scale) {

	}

	Transform::Transform(const math::Vector3& pos)
		: position(pos), 
		  rotation(), 
		  scale(1,1,1) {
	}

	Transform::Transform(const math::Quaternion& rot)
		: position(0,0,0),
	      rotation(rot), 
	      scale(1,1,1) {

	}
	

	Transform::Transform(const math::Vector3& pos, const math::Quaternion& rot)
		: position(pos),
		  rotation(rot),
		  scale(1, 1, 1) {
	}

}