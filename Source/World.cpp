//STD Headers
#include <iostream>

//Library Headers


//Coati Headers
#include "World.h"
#include "MessageBus.h"

World::World(std::shared_ptr<MessageBus> bus){
	this->GameMessageBus = GameMessageBus;

	std::cout << "Hello world!\n";
}


World::~World(){
	std::cout << "Goodbye world!\n";
}

void World::Update(double deltaSeconds){

}
