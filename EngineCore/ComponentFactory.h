#pragma once
//STD Headers

//Library Headers
#include "nlohmann/json.hpp"

//Void Engine Headers
#include "Entity.h"
#include "Component.h"
#include "ResourceAllocator.h"
#include "Model.h"

namespace core {

	class ComponentFactory	{
	public:
		/**
		 * Constructor
		 * @param textureAllocator ResourceAllocator to allow loading and caching of texture loads.
		 */
		ComponentFactory(ResourceAllocatorPtr<Model> modelAllocator);

		/**
		 * Creates and attatches components specified by componentList to parent
		 * @param parent The entity that will receive references to the newly created components
		 * @param componentList The list of components to create
		 */
		void ProcessComponentData(Entity* parent, const nlohmann::json& componentList);

		/**
		 * Helper function to create components and attatch them to a parent
		 * @param parent The entity to attach this component to
		 * @param componentData The data needed to construct that component
		 * @return nullptr if construction fails, the Component if it's successful.
		 */
		Component* CreateComponent(Entity* parent, const nlohmann::json& componentData);

	private:
		/** Allows loading and caching of textures */
		ResourceAllocatorPtr<Model> ModelCache;
	};

}
