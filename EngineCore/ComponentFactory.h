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

namespace core {
	//Forward class declarations
	class Level;

	class ComponentFactory	{
	public:

		ComponentFactory(Level* currLevel);

		void ProcessComponentData(Entity* parent, const nlohmann::json& componentList);

		/**
		 * Helper function to create components and attatch them to a parent
		 * @param parent The entity to attach this component to
		 * @param componentData The data needed to construct that component
		 * @return nullptr if construction fails, the Component if it's successful.
		 */
		Component* CreateComponent(Entity* parent, const nlohmann::json& componentData);

	private:
		Level* CurrentLevel;
	};

}
