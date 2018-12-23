#pragma once

//STD Headers
#include <chrono>
#include <memory>

//Library Headers

//Coati Headers
#include "MessageBusNode.h"

//Forward Class declarations
class MessageBus;


class AudioManager : MessageBusNode{
private:
	//Private class members

public:
	//CTORS
	AudioManager(std::shared_ptr<MessageBus> GameMessageBus);
	~AudioManager();

private:
	//Private member functions
	

public:
	//Public Member functions
	virtual void ReceiveMessage(Message message);
};
