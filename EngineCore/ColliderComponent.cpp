//STD Headers

//Library Headers

//Void Engine Headers
#include "ColliderComponent.h"

namespace core {

	ENABLE_FACTORY(ColliderComponent, Component)

	ColliderComponent::ColliderComponent() : CollisionVolume(nullptr) {
		
	}

	void ColliderComponent::Initialize() {

	}

	utils::Name ColliderComponent::GetTypename() {
		return utils::Name(TypeName<ColliderComponent>::GetName());
	}

	utils::Name ColliderComponent::GetStaticTypename() {
		return utils::Name(TypeName<ColliderComponent>::GetName());
	}
}