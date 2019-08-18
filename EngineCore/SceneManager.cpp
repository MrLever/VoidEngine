//STD Headers

//Library Headers

//Void Engine Headers
#include "EntityManager.h"
#include "SceneManager.h"

namespace EngineCore {

	EngineCore::SceneManager::SceneManager()
	{
	}

	void SceneManager::UpdateScene(double deltaTime) {
		for (auto& entity : Entities) {
			entity->Tick(deltaTime);
		}
	}

	void SceneManager::DrawScene() {
	}

	void SceneManager::StartLevel() {
	}

}