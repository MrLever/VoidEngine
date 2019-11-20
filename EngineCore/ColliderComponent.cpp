//STD Headers

//Library Headers

//Void Engine Headers
#include "ColliderComponent.h"
#include "Factory.h"

namespace core {

	ENABLE_FACTORY(ColliderComponent, Component);

	// Static variable initialization
	utils::Table
		<utils::Name, utils::Name, std::function<Manifold*(ColliderComponent*, ColliderComponent*)>>
	ColliderComponent::CollisionDetectionJumpTable;

	utils::Table
		<utils::Name, utils::Name, std::function<void(Manifold*)>>
	ColliderComponent::CollisionResolutionJumpTable;

	ColliderComponent::ColliderComponent() : Layer(0), Shape(nullptr) {
		
	}

	utils::Name ColliderComponent::GetTypename() const {
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

	void ColliderComponent::ResolveCollision(Manifold* collision) {
		auto colliderType1 = collision->ColliderA->Shape->GetTypename();
		auto colliderType2 = collision->ColliderB->Shape->GetTypename();

		auto callback = CollisionResolutionJumpTable.Find(colliderType1, colliderType2);

		if (callback) {
			callback->operator()(collision);
		}
	}

	const Collider* ColliderComponent::GetShape() const {
		return Shape;
	}
}