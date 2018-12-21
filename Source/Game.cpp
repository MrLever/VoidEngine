//STD Headers
#include <iostream>

//Library Headers


//Coati Headers
#include "Game.h"

#include "World.h"
#include "MessageBus.h"

//CTORS
Game::Game(std::string name) : GameName(name) {
	//Init Frameworks
	//Init Game
	InitGame();
	//Start game loop

	GameLoop();

}

Game::~Game(){
	
}

//Private Functions

//Initializes engine framework objects
void Game::InitGame(){
	GameWorld = std::make_unique<World>();
	GameMessageBus = std::make_unique<MessageBus>();
}


void Game::GameLoop(){
	auto previousTime = Timer::now();
	while (true) {
		//Get current time
		auto currentTime = Timer::now();
		std::chrono::duration<double> deltaSeconds = currentTime - previousTime;

		//Tell the world to update
		GameWorld->Update(deltaSeconds.count());

		//Update previous time
		previousTime = Timer::now();
	}
	return;
}
