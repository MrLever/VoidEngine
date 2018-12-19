//STD Headers
#include <iostream>
#include <chrono>

//Library Headers


//Coati Headers
#include "World.h"

int main() {
	using Timer = std::chrono::high_resolution_clock;
	World gameWorld;
	   	 
	auto previousTime = Timer::now();
	gameWorld.StartGame();
	while (true) {
		//Get current time
		auto currentTime = Timer::now();
		std::chrono::duration<double> deltaSeconds = currentTime - previousTime;

		//Tell the world to update
		gameWorld.Update(deltaSeconds.count());

		//Update previous time
		previousTime = Timer::now();
		break;
	}
	return 0;
}

