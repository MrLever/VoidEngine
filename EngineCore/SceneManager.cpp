//STD Headers

//Library Headers

//Void Engine Headers
#include "SceneManager.h"
#include "ThreadPool.h"
#include "ResourceManager.h"

namespace EngineCore {

	EngineCore::SceneManager::SceneManager(
			ThreadPoolPtr pool,	ResourceManagerPtr resourceManager
		) : GameThreadPool(std::move(pool)), GameResourceManager(std::move(resourceManager)) {

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