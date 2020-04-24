//STD Headers

//Library Headers

//Void Engine Headers
#include "physics/components/ColliderComponent.h"
#include "utils/factory/Factory.h"

namespace core {

	TYPE_INFO_IMPL(ColliderComponent)

	ENABLE_FACTORY(ColliderComponent, Component);

	// Static variable initialization
	utils::Table<
		utils::Name, 
		utils::Name, 
		std::function<Manifold*(ColliderComponent*, ColliderComponent*)>
	> ColliderComponent::s_CollisionDetectionJumpTable;

	ColliderComponent::ColliderComponent() : collisionLayer(0), shape(nullptr) {
		
	}

	ColliderComponent::~ColliderComponent() {

	}

	void ColliderComponent::Initialize() {
		if (configData.find("collisionLayer") != configData.end()) {
			collisionLayer = configData["collisionLayer"].get<unsigned>();
		}

		shape.reset(utils::FactoryBase<Collider>::Create(configData["shape"]["type"].get<std::string>()));
		shape->SetConfigData(configData["shape"]);
		shape->Initialize();
		shape->SupplyEntityScale(transform->scale);
	}

	void ColliderComponent::Draw() {

	}
	
	Manifold* ColliderComponent::DetectCollision(ColliderComponent* other) {
		auto colliderType1 = shape->GetTypename();
		auto colliderType2 = other->shape->GetTypename();

		auto callback = s_CollisionDetectionJumpTable.Find(colliderType1, colliderType2);

		if (callback) {
			return callback->operator()(this, other);
		}
		else {
			return nullptr;
		}
	}

	const Collider* ColliderComponent::GetShape() const {
		return shape.get();
	}

	unsigned ColliderComponent::GetCollisionLayer() const {
		return collisionLayer;
	}
}