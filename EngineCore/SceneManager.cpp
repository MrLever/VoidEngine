//STD Headers

//Library Headers

//Void Engine Headers
#include "SceneManager.h"

namespace EngineCore {

	EngineCore::SceneManager::SceneManager() {
	}

	SceneManager::~SceneManager() {
	}

	void SceneManager::UpdateScene(double deltaTime) {
		/*for (auto entity : Entities) {
			entity->Tick(deltaTime);
		}*/
	}

	void SceneManager::DrawScene() {
	}

	void SceneManager::StartLevel() {
		/*for (auto& entity : Entities) {
			entity->BeginPlay();
		}*/
	}

}