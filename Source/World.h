#pragma once

//STD Headers
#include <chrono>
#include <memory>
#include <vector>

//Project-Coati Headers
#include "Level.h"

//Forward Class declarations
class MessageBus;

class World{
private:
	//Private Class Members
	std::shared_ptr<MessageBus> GameMessageBus;
	std::unique_ptr<Level> currentLevel;

	std::vector<Level> levelList;

public:
	//CTORS
	World(std::shared_ptr<MessageBus> GameMessageBus);
	~World();


private:
	//Private Class Methods

public:
	//Public Class Methods
	void Update(double deltaSeconds);

	void SwitchLevel(int levelID);

	void Tick();
};

