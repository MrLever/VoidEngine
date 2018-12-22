#pragma once

//STD Headers
#include <queue>

//Library Headers


//Forward Class declarations


class MessageBus {
private:
	//Private Class members
	std::queue<int> MessageQueue;

public:
	MessageBus();
	~MessageBus();

private:
	//Private member functions

public:
	void PostMessage();
	void DispatchMessages();
	void AddReciever();

};

