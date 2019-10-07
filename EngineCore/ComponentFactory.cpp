//STD Headers

//Library Headers

//Void engine headers
#include "ComponentFactory.h"
#include "WindowManager.h"
#include "Level.h"
#include "Texture.h"

//SuperVoid Component Includes
#include "FlyingMovementComponent.h"
#include "GraphicsComponent.h"
#include "CameraComponent.h"
#include "PanMovementComponent.h"

namespace core {
	ComponentFactory::ComponentFactory(ResourceAllocatorPtr<Texture> textureAllocator) 
		: TextureCache(textureAllocator) {

	}

	void ComponentFactory::ProcessComponentData(Entity* parent, const nlohmann::json& componentList) {
		for (auto& componentData : componentList) {
			auto component = CreateComponent(parent, componentData);

			if (component) {
				parent->AddComponent(component);
			}
		}
	}

	Component* ComponentFactory::CreateComponent(Entity* parent, const nlohmann::json& componentData) {
		std::string type = componentData["type"].get<std::string>();
		Component* component = nullptr;

		if ( type == "CameraComponent") {
			auto tempHandle = new CameraComponent(parent);
			WindowManager::GetActiveWindow()->SetView(parent, tempHandle);
			component = tempHandle;
		}
		else if (type == "FlyingMovementComponent") {
			auto tempHandle = new FlyingMovementComponent(parent);
			
			float movespeed = componentData["speed"].get<float>();
			tempHandle->SetMoveSpeed(movespeed);

			component = tempHandle;
		}
		else if (type == "PanMovementComponent") {
			auto tempHandle = new PanMovementComponent(parent);

			float movespeed = componentData["speed"].get<float>();
			tempHandle->SetMoveSpeed(movespeed);

			component = tempHandle;
		}
		else if (type == "GraphicsComponent") {
			//Load entity model
			std::vector<float> verts;

			for (auto vert : componentData["model"]) {
				verts.push_back(vert.get<float>());
			}

			//Populate entity draw data
			GraphicsComponent* entityDrawData = new GraphicsComponent(parent);
			entityDrawData->SetModel(verts);
			entityDrawData->AddMaterial(
				componentData["material"]["name"].get<std::string>(),
				componentData["material"]["vertexShader"].get<std::string>(),
				componentData["material"]["fragmentShader"].get<std::string>()
			);

			auto textureList = componentData["textures"];

			int i = 0;
			for (auto& textureMetaDeta : textureList) {
				auto texture = TextureCache->GetResource(textureMetaDeta["location"].get<std::string>());
				texture->SetName(textureMetaDeta["name"].get<std::string>());

				entityDrawData->AddTexture(texture, i);
				i++;
			}

			component = entityDrawData;
		}
		else {
			utils::Logger::LogError("Component Factory recieved request to construct unkown component [" + type + "].");
		}

		return component;
	}

}