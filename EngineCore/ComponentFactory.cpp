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
	ComponentFactory::ComponentFactory(ResourceAllocatorPtr<Model> modelAllocator) 
		: ModelCache(modelAllocator) {

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
			//Populate entity draw data
			GraphicsComponent* entityDrawData = new GraphicsComponent(parent);
			auto model = ModelCache->GetResource(componentData["model"].get<std::string>());
			model->Initialize();
			entityDrawData->SetModel(model);

			component = entityDrawData;
		}
		else {
			utils::Logger::LogError("Component Factory recieved request to construct unkown component [" + type + "].");
		}

		return component;
	}

}