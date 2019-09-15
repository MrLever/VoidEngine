#pragma once
//STD Headers
#include <memory>
#include <vector>
#include <string>

//Library Headers
#include "nlohmann/json.hpp"

//Void Engine Headers
#include "Entity.h"
#include "GraphicsComponent.h"

namespace EngineCore {
	
	/**
	 * @class EntityFactory
	 * @brief Factory class to generate game enities from JSON data
	 */
	class EntityFactory	{
	public:
		[[nodiscard]] std::vector<std::shared_ptr<Entity>> CreateEntityList(const nlohmann::json& entityList);

		template<class T>
		[[nodiscard]] std::shared_ptr<T> CreateEntity(const nlohmann::json& entityData);

	};

	template<class T>
	inline std::shared_ptr<T> EntityFactory::CreateEntity(const nlohmann::json& entityData) {
		auto entityName = entityData["name"].get<std::string>();
		auto entity = std::make_shared(entityName);

		


		return entity;
	}
}