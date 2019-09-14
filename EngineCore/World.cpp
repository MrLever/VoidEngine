//STD Headers
#include <iostream>
#include <utility>
#include <memory>

//Library Headers


//Coati Headers
#include "World.h"


namespace EngineCore {

	World::World(std::unique_ptr<SceneManager> sceneManager) : GameSceneManager(std::move(sceneManager)) {
		GameMessageBus = std::make_shared<MessageBus>();
		GameConsole = std::make_shared<Console>(GameMessageBus);

		GameConsole->Log("Hello World", LogLevel::INFO);

		GameSceneManager->LoadLevel("Resources/Levels/DemoLevel.json");
	}

	World::~World() {
		GameConsole->Log("Goodbye World", LogLevel::INFO);
	}

	void World::Update(double deltaSeconds) {
		//Triggers Events
		GameMessageBus->DispatchMessages();

		//Ticks Entities
		GameSceneManager->UpdateScene(deltaSeconds);
	}

	std::vector<std::shared_ptr<Entity>> World::GetCurrentScene() {
		return GameSceneManager->GetScene();
	}

}