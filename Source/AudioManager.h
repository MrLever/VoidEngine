#pragma once

//STD Headers
#include <chrono>
#include <memory>

//Library Headers

//Coati Headers
#include "MessageReceiver.h"

//Forward Class declarations
class MessageBus;


class AudioManager : MessageReceiver{
private:
	//Private class members
	std::shared_ptr<MessageBus> GameMessageBus;

public:
	//CTORS
	AudioManager(std::shared_ptr<MessageBus> GameMessageBus);
	~AudioManager();

private:
	//Private member functions

public:
	//Public Member functions
};
