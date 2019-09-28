//STD Headers

//Library Headers

//Void engine headers
#include "ComponentFactory.h"
#include "Level.h"

namespace EngineCore {
	ComponentFactory::ComponentFactory(Level* currLevel) {
		CurrentLevel = currLevel;
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
			CurrentLevel->ActiveCamera = tempHandle;
			component = tempHandle;
		}
		else if (type == "FlyingMovementComponent") {
			auto tempHandle = new FlyingMovementComponent(parent);
			
			float movespeed = componentData["speed"].get<float>();
			tempHandle->SetMoveSpeed(movespeed);

			component = tempHandle;
		}

		return nullptr;
	}

}