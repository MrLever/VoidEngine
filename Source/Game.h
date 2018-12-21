#pragma once
//STD Headers
#include <chrono>
#include <memory>

//Library Headers


//Forward Class declarations
class World;
class MessageBus;

class Game{
	using Timer = std::chrono::high_resolution_clock;
private:
	//Private Class Members
	std::unique_ptr<World> GameWorld;
	std::unique_ptr<MessageBus> GameMessageBus;

	std::string GameName;

public:
	Game(std::string name);
	~Game();

private:
	void InitGame();
	void GameLoop();
};

