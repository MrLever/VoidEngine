//STD Headers

//Library Headers

//Void Engine Headers
#include "ColliderComponent.h"
#include "Factory.h"

namespace core {

	ENABLE_FACTORY(ColliderComponent, Component);

	utils::Table
		<utils::Name, utils::Name, std::function<bool(ColliderComponent*, ColliderComponent*)>>
	ColliderComponent::CollisionJumpTable;

	ColliderComponent::ColliderComponent() : Layer(0), Shape(nullptr) {
		
	}

	utils::Name ColliderComponent::GetTypename() {
		return utils::Name(TypeName<ColliderComponent>::GetName());
	}

	utils::Name ColliderComponent::GetStaticTypename() {
		return utils::Name(TypeName<ColliderComponent>::GetName());
	}

	void ColliderComponent::Initialize() {
		Position = Parent->GetPostion();
		Shape = utils::FactoryBase<Collider>::Create(ComponentData["shape"]["type"].get<std::string>());
		Shape->SetConfigData(ComponentData["shape"]);
		Shape->Initialize();
	}

	void ColliderComponent::Tick(float deltaTime) {
		Position = Parent->GetPostion();
	}
	
	bool ColliderComponent::DetectCollision(ColliderComponent* other) {
		auto colliderType1 = Shape->GetTypename();
		auto colliderType2 = other->Shape->GetTypename();

		auto callback = CollisionJumpTable.Find(colliderType1, colliderType2);

		if (callback) {
			return callback->operator()(this, other);
		}
		else {
			return false;
		}
	}
}