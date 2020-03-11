#include "..\include\core\SceneLoader.h"
//STD Headers

//Library Headers

//Void Engine Headers

namespace core {

	SceneLoader::SceneLoader() {

	}

	SceneLoader::~SceneLoader() {

	}

	void SceneLoader::LoadLevel(Scene* scene, const std::string& levelPath) {
		auto level = LevelCache.GetResource(levelPath);

		utils::Logger::LogInfo("Initializing Level " + level->GetName().StringID);
		scene->m_ControlFilePath = level->GetAttribute<std::string>("controlFile");

		auto lightSettings = level->GetAttribute<nlohmann::json>("lightSettings");

		//Gather scene's ambient light data
		scene->m_LightingEnvironment.AmbientLightColor.X = lightSettings["ambientLightColor"][0];
		scene->m_LightingEnvironment.AmbientLightColor.Y = lightSettings["ambientLightColor"][1];
		scene->m_LightingEnvironment.AmbientLightColor.Z = lightSettings["ambientLightColor"][2];
		scene->m_LightingEnvironment.AmbientLightColor.W = lightSettings["ambientLightColor"][3];
		scene->m_LightingEnvironment.AmbientLightIntensity = lightSettings["ambientLightIntensity"];

		auto entityList = level->GetAttribute<nlohmann::json>("entities");

		for (auto& entityData : entityList) {
			auto entityType = entityData["type"].get<std::string>();
			auto entity = utils::FactoryBase<Entity>::Create(entityType);
			if (entity == nullptr) {
				utils::Logger::LogWarning("Entity type " + entityType + " was not constructed properly. Please register its factory.");
				continue;
			}

			entity->SetConfigData(entityData);
			entity->SetScene(scene);

			nlohmann::json componentList;
			if (entityData.find("components") != entityData.end()) {
				componentList = entityData["components"];
			}

			for (auto componentEntry : componentList) {
				auto componentType = componentEntry["type"].get<std::string>();
				auto component = utils::FactoryBase<Component>::Create(componentType);
				if (component) {
					entity->AddComponent(component);
					component->SetConfigData(componentEntry);
				}
			}

			entity->Initialize();
			scene->m_Entities.emplace_back(entity);
		}
	}

}
