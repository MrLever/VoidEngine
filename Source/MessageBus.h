#pragma once

//STD Headers
#include <functional>
#include <queue>
#include <vector>

//Library Headers

//Coati Headers
#include "Message.h"

//Forward Class declarations

class MessageBus {
private:
	//Private Class members
	std::queue<Message> Messages;
	std::vector<std::function<void(Message)>> Recievers;

public:
	MessageBus();
	~MessageBus();

private:
	//Private member functions

public:
	void AddReciever(std::function<void(Message)> messageReceiver);
	void PublishMessage(Message message);
	void DispatchMessages();


};

