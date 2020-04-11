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

	void ColliderComponent::Initialize() {
		if (configData.find("collisionLayer") != configData.end()) {
			collisionLayer = configData["collisionLayer"].get<unsigned>();
		}

		shape = utils::FactoryBase<Collider>::Create(configData["shape"]["type"].get<std::string>());
		shape->SetConfigData(configData["shape"]);
		shape->Initialize();

		colliderShader = std::make_shared<ShaderProgram>(
			"ColliderShader",
			new Shader(
				ShaderType::VERTEX,
				"Resources/Shaders/default.vert"
			),
			new Shader(
				ShaderType::FRAGMENT,
				"Resources/Shaders/default.frag"
			)
		);

	}

	void ColliderComponent::Draw() {
		auto transformMatrix = glm::mat4(1.0f);
		auto position = parent->GetPosition();
		transformMatrix = glm::translate(
			transformMatrix, 
			glm::vec3(position.X - 1, position.Y, position.Z)
		);

		shape->Draw(colliderShader, transformMatrix);
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
		return shape;
	}

	unsigned ColliderComponent::GetCollisionLayer() const {
		return collisionLayer;
	}
}