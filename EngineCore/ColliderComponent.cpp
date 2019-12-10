//STD Headers

//Library Headers

//Void Engine Headers
#include "ColliderComponent.h"
#include "Factory.h"

namespace core {

	TYPE_INFO_IMPL(ColliderComponent)

	ENABLE_FACTORY(ColliderComponent, Component);

	// Static variable initialization
	utils::Table
		<utils::Name, utils::Name, std::function<Manifold*(ColliderComponent*, ColliderComponent*)>>
	ColliderComponent::CollisionDetectionJumpTable;

	ColliderComponent::ColliderComponent() : CollisionLayer(0), Shape(nullptr) {
		
	}

	void ColliderComponent::Initialize() {
		Position = Parent->GetPostion();

		if (ConfigData.find("collisionLayer") != ConfigData.end()) {
			CollisionLayer = ConfigData["collisionLayer"].get<unsigned>();
		}

		Shape = utils::FactoryBase<Collider>::Create(ConfigData["shape"]["type"].get<std::string>());
		Shape->SetConfigData(ConfigData["shape"]);
		Shape->Initialize();
	}

	void ColliderComponent::Tick(float deltaTime) {
		Position = Parent->GetPostion();
	}
	
	Manifold* ColliderComponent::DetectCollision(ColliderComponent* other) {
		auto colliderType1 = Shape->GetTypename();
		auto colliderType2 = other->Shape->GetTypename();

		auto callback = CollisionDetectionJumpTable.Find(colliderType1, colliderType2);

		if (callback) {
			return callback->operator()(this, other);
		}
		else {
			return nullptr;
		}
	}

	const Collider* ColliderComponent::GetShape() const {
		return Shape;
	}

	unsigned ColliderComponent::GetCollisionLayer() const {
		return CollisionLayer;
	}
}