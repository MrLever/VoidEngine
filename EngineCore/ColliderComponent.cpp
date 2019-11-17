//STD Headers

//Library Headers

//Void Engine Headers
#include "ColliderComponent.h"
#include "Factory.h"

namespace core {

	ENABLE_FACTORY(ColliderComponent, Component);

	utils::Table
		<utils::Name, utils::Name, std::function<bool(Collider*, Collider*)>>
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
		return false;
	}

	void ColliderComponent::RegisterCollisionCallback(
		utils::Name a,
		utils::Name b,
		std::function<bool(Collider*, Collider*)> callback
		) {

		if (CollisionJumpTable.Find(a, b) != nullptr) {
			utils::Logger::LogWarning(
				"CollisionCallback [" + 
				a.StringID + "][" + 
				b.StringID + "] has already been registered");
			return;
		}

		CollisionJumpTable[a][b] = callback;
	}
}