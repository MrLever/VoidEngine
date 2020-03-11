//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/TimeUtils.h"

#include "gameplay_framework/Entity.h"
#include "rendering/components/GraphicsComponent.h"
#include "rendering/ShaderProgram.h"
#include "rendering/Texture.h"

namespace core {

	TYPE_INFO_IMPL(GraphicsComponent)

	ENABLE_FACTORY(GraphicsComponent, Component)

	GraphicsComponent::GraphicsComponent()
		: m_TransformMatrix(1.0f), m_Shader(nullptr), m_IsValid(true) {

	}

	GraphicsComponent::~GraphicsComponent() {

	}

	void GraphicsComponent::Initialize() {
		if (!Parent) {
			return;
		}
		
		Position = Parent->GetPostion();
		Rotation = Parent->GetRotation();

		auto modelCache = std::make_shared<utils::ResourceAllocator<Model>>();

		m_Model = modelCache->GetResource(ConfigData["model"].get<std::string>());
		m_Model->Initialize();

		if (ConfigData.find("shader") != ConfigData.end()) {
			AddMaterial(
				ConfigData["shader"]["name"].get<std::string>(),
				ConfigData["shader"]["vertexShader"].get<std::string>(),
				ConfigData["shader"]["fragmentShader"].get<std::string>()
			);
		}
		else {
			AddMaterial("DefaultMaterial", "Resources/Shaders/default.vert", "Resources/Shaders/default.frag");
		}
	}

	void GraphicsComponent::SetModel(std::shared_ptr<Model> model) {
		m_Model = std::move(model);
	}

	void GraphicsComponent::AddMaterial(const std::string& name, const std::string& vertShaderPath, const std::string& fragShaderPath) {
		m_Shader = std::make_shared<ShaderProgram>(
			name,
			new Shader(
				ShaderType::VERTEX,
				vertShaderPath
			),
			new Shader(
				ShaderType::FRAGMENT,
				fragShaderPath
			)
		);
	}

	void GraphicsComponent::Draw() {
		Position = Parent->GetPostion();
		Rotation = math::Quaternion(Parent->GetRotation());

		m_TransformMatrix = glm::mat4(1.0f);
		m_TransformMatrix = glm::translate(m_TransformMatrix, glm::vec3(Position.X, Position.Y, Position.Z));
		
		auto rotation = Rotation.ToEuler();
		m_TransformMatrix = glm::rotate(
			m_TransformMatrix, glm::radians(rotation.Roll), glm::vec3(1.0f, 0.0f, 0.0f)
		);


		m_TransformMatrix = glm::rotate(
			m_TransformMatrix, glm::radians(rotation.Pitch), glm::vec3(0.0f, 1.0f, 0.0f)
		);

		m_TransformMatrix = glm::rotate(
			m_TransformMatrix, glm::radians(rotation.Yaw), glm::vec3(0.0f, 0.0f, 1.0f)
		);
		

		if (m_Model) {
			m_Model->Draw(m_Shader, m_TransformMatrix);
		}
	}

}