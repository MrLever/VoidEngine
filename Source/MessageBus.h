#pragma once

//STD Headers
#include <functional>
#include <queue>
#include <vector>

//Library Headers

//Coati Headers
#include "Message.h"

//Forward Class declarations
class MessageBusNode;

class MessageBus {
	typedef struct Subscriber {
		std::function<void(Message)> receivingFunction;
		int subscriptionFlag;
		Subscriber(std::function<void(Message)> fn, int flag) : receivingFunction(fn), subscriptionFlag(flag) {
		
		}
	}Subscriber;
private:
	//Private Class members
	std::queue<Message> Messages;
	std::vector<Subscriber> Receivers;

public:
	MessageBus();
	~MessageBus();

private:
	//Private member functions

public:
	void AddReciever(MessageBusNode* receiver, int subscriptionFlag);
	void PublishMessage(Message message);
	void DispatchMessages();


};

