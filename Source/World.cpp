//STD Headers
#include <iostream>

//Library Headers


//Coati Headers
#include "World.h"

World::World(){
	std::cout << "Hello world!\n";
}


World::~World(){
	std::cout << "Goodbye world!\n";
}

void World::StartGame() {
	std::cout << "Starting game";
}

void World::Update(double deltaTime){
	//Process Input
	//Update Acotrs
	//Render
}
