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
		/**
		 * Function to create a set of entities from JSON data
		 * @param entityList The data for the entities to spawn
		 */
		[[nodiscard]] std::vector<std::shared_ptr<Entity>> CreateEntityList(const nlohmann::json& entityList);

		/**
		 * Function to create a single entity from JSON data
		 * @param entityData The data for a single entity
		 */
		template<class T>
		[[nodiscard]] std::shared_ptr<T> CreateEntity(const nlohmann::json& entityData);

	};

	template<class T>
	inline std::shared_ptr<T> EntityFactory::CreateEntity(const nlohmann::json& entityData) {
		auto entityName = entityData["name"].get<std::string>();
		auto entity = std::make_shared<T>(entityName);

		EngineMath::Vector3 position;
		position.X = entityData["location"][0].get<float>();
		position.Y = entityData["location"][1].get<float>();
		position.Z = entityData["location"][2].get<float>();

		entity->SetPosition(position);
		
		std::vector<float> verts;
		auto graphicsData = entityData["graphicsComponent"];

		for (auto vert : graphicsData["model"]) {
			verts.push_back(vert.get<float>());
		}

		GraphicsComponent* entityDrawData = new GraphicsComponent();
		entityDrawData->SetModel(verts);
		entityDrawData->AddMaterial(
			graphicsData["material"]["name"].get<std::string>(),
			graphicsData["material"]["vertexShader"].get<std::string>(),
			graphicsData["material"]["fragmentShader"].get<std::string>()
		);
		entityDrawData->AddTexture(
			graphicsData["texture"].get<std::string>()
		);

		entity->SetGraphicsComponent(entityDrawData);

		return entity;
	}
}