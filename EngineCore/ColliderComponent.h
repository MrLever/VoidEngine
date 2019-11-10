#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "Component.h"
#include "Collider.h"

namespace core {

	class CollisionComponent : public Component {

	private:
		Collider* CollisionVolume;
	};

}

