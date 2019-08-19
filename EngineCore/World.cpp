//STD Headers
#include <iostream>
#include <utility>
#include <memory>

//Library Headers


//Coati Headers
#include "World.h"


namespace EngineCore {

	World::World() {
		std::cout << "Hello world!\n";
		GameMessageBus = std::make_shared<MessageBus>();
		GameConsole = std::make_shared<Console>(GameMessageBus);
	}

	World::~World() {
		std::cout << "Goodbye world!\n";
	}

	void World::Update(double deltaSeconds) {
		//Triggers Events
		GameMessageBus->DispatchMessages();

		GameSceneManager->UpdateScene(deltaSeconds);
	}

}