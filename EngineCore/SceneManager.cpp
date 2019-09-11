//STD Headers

//Library Headers

//Void Engine Headers
#include "SceneManager.h"

namespace EngineCore {

	EngineCore::SceneManager::SceneManager() {
	}

	SceneManager::~SceneManager() {
	}

	void SceneManager::LoadLevel(const Level& level) {
		
	}

	void SceneManager::UpdateScene(double deltaTime) {
		for (auto entity : Entities) {
			entity->Tick(deltaTime);
		}
	}

	void SceneManager::StartLevel() {
		for (auto& entity : Entities) {
			entity->BeginPlay();
		}
	}

	std::vector<std::shared_ptr<Entity>> SceneManager::GetScene() {
		return Entities;
	}

}