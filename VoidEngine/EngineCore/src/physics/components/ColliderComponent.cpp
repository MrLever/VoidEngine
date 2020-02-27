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

	ColliderComponent::ColliderComponent() : m_CollisionLayer(0), Shape(nullptr) {
		
	}

	void ColliderComponent::Initialize() {
		Position = Parent->GetPostion();

		if (ConfigData.find("collisionLayer") != ConfigData.end()) {
			m_CollisionLayer = ConfigData["collisionLayer"].get<unsigned>();
		}

		Shape = utils::FactoryBase<Collider>::Create(ConfigData["shape"]["type"].get<std::string>());
		Shape->SetConfigData(ConfigData["shape"]);
		Shape->Initialize();

		m_ColliderShader = std::make_shared<ShaderProgram>(
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

	void ColliderComponent::Tick(float deltaTime) {
		Position = Parent->GetPostion();
	}

	void ColliderComponent::Draw() {
		auto transformMatrix = glm::mat4(1.0f);
		transformMatrix = glm::translate(transformMatrix, glm::vec3(Position.X - 1, Position.Y, Position.Z));

		auto rotation = Rotation.ToEuler();
		transformMatrix = glm::rotate(
			transformMatrix, glm::radians(rotation.Yaw), glm::vec3(1.0f, 0.0f, 0.0f)
		);

		transformMatrix = glm::rotate(
			transformMatrix, glm::radians(rotation.Pitch), glm::vec3(0.0f, 1.0f, 0.0f)
		);

		transformMatrix = glm::rotate(
			transformMatrix, glm::radians(rotation.Roll), glm::vec3(0.0f, 0.0f, 1.0f)
		);

		Shape->Draw(m_ColliderShader, transformMatrix);
	}
	
	Manifold* ColliderComponent::DetectCollision(ColliderComponent* other) {
		auto colliderType1 = Shape->GetTypename();
		auto colliderType2 = other->Shape->GetTypename();

		auto callback = s_CollisionDetectionJumpTable.Find(colliderType1, colliderType2);

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
		return m_CollisionLayer;
	}
}