//STD Headers

//Library Headers

//Void Engine Headers
#include "ColliderComponent.h"

namespace core {

	utils::Table
		<utils::Name, utils::Name, std::function<bool(ColliderComponent*, ColliderComponent*)>>
	ColliderComponent::CollisionJumpTable;

	ColliderComponent::ColliderComponent() : Layer(0) {
		
	}

	utils::Name ColliderComponent::GetTypename() {
		return utils::Name(TypeName<ColliderComponent>::GetName());
	}

	utils::Name ColliderComponent::GetStaticTypename() {
		return utils::Name(TypeName<ColliderComponent>::GetName());
	}
	
	bool ColliderComponent::DetectCollision(ColliderComponent* other) {
		auto i = GetTypename();
		auto j = other->GetTypename();
		auto collisionCallback = CollisionJumpTable.Find(i, j);
		if (collisionCallback) {
			return collisionCallback->operator()(this, other);
		}
		else {
			return false;
		}
	}
}