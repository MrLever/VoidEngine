//STD Headers

//Library Headers

//Void Engine Headers
#include "EntityFactory.h"
//#include "CubeEntity.h"

namespace EngineCore {

	std::vector<std::shared_ptr<Entity>> EntityFactory::CreateEntityList(const nlohmann::json& entityList) {
		std::vector<std::shared_ptr<Entity>> scene;

		for (const auto& entity : entityList) {
			std::string type = entity["name"].get<std::string>();

			if (type == "CubeEntity") {
				//scene.push_back(CreateEntity<CubeEntity>())
			}

		}

		return std::vector<std::shared_ptr<Entity>>();
	}

}