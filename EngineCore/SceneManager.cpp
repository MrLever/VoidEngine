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

	void SceneManager::LoadLevel(const std::string& levelPath) {
		Level l(levelPath);
		l.Load();

		std::cout << std::filesystem::current_path();

		std::cout << "Level Name: " << l.GetName() << "\n";

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