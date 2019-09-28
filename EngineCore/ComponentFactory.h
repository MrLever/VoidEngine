#pragma once
//STD Headers

//Library Headers
#include "nlohmann/json.hpp"

//Void Engine Headers
#include "Entity.h"
#include "Component.h"
#include "FlyingMovementComponent.h"
#include "GraphicsComponent.h"
#include "CameraComponent.h"

namespace EngineCore {
	//Forward class declarations
	class Level;

	class ComponentFactory	{
	public:

		ComponentFactory(Level* currLevel);

		void ProcessComponentData(Entity* parent, const nlohmann::json& componentList);

		Component* CreateComponent(Entity* parent, const nlohmann::json& componentData);

	private:
		Level* CurrentLevel;
	};

}
