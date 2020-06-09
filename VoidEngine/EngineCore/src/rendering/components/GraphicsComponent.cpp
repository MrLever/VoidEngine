//STD Headers

//Library Headers
#include <glm/gtx/quaternion.hpp>

//Void Engine Headers
#include "utils/TimeUtils.h"

#include "gameplay_framework/Entity.h"
#include "rendering/components/GraphicsComponent.h"
#include "rendering/ShaderProgram.h"
#include "rendering/Texture.h"

namespace core {

	ENABLE_FACTORY(GraphicsComponent, Component)

	GraphicsComponent::GraphicsComponent()
		: transformationMatrix(1.0f), shader(nullptr), isValid(true) {

	}

	GraphicsComponent::~GraphicsComponent() {

	}

	void GraphicsComponent::Initialize() {
		if (!parent) {
			return;
		}
		
		auto modelCache = std::make_shared<utils::ResourceAllocator<Model>>();

		model = modelCache->GetResource(configData["model"].get<std::string>());
		model->Initialize();

		if (configData.find("shader") != configData.end()) {
			AddMaterial(
				configData["shader"]["name"].get<std::string>(),
				configData["shader"]["vertexShader"].get<std::string>(),
				configData["shader"]["fragmentShader"].get<std::string>()
			);
		}
		else {
			AddMaterial("DefaultMaterial", "Assets/Default/Shaders/default.vert", "Assets/Default/Shaders/default.frag");
		}
	}

	void GraphicsComponent::AddMaterial(const std::string& name, const std::string& vertShaderPath, const std::string& fragShaderPath) {
		shader = std::make_shared<ShaderProgram>(
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
		transformationMatrix = glm::mat4(1.0f);

		//Translate
		auto position = parent->GetPosition();
		transformationMatrix = glm::translate(
			transformationMatrix, 
			glm::vec3(position.X, position.Y, position.Z)
		);

		//Rotate
		auto rotation = math::Quaternion(parent->GetRotation()).Normalize();
		auto rotationMatrix = glm::toMat4(glm::quat(rotation.W, rotation.X, rotation.Y, rotation.Z));
		transformationMatrix = transformationMatrix * rotationMatrix;

		//Scale
		auto scale = parent->GetScale();
		transformationMatrix = glm::scale(
			transformationMatrix, 
			glm::vec3(scale.X, scale.Y, scale.Z)
		);
		
		if (model) {
			model->Draw(shader, transformationMatrix);
		}
	}

}