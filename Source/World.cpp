//STD Headers
#include <iostream>

//Library Headers


//Coati Headers
#include "World.h"

World::World(){
	//Init Input
	//Init Render
	std::cout << "Hello world!\n";
}


World::~World(){
	std::cout << "Goodbye world!\n";
}

void World::Update(double deltaTime){
	//Process Events
	//Tick Actors
	//Render Level
}
