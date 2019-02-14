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
		MessageType subscriptionFlag;
		Subscriber(std::function<void(Message)> fn, MessageType flag) : receivingFunction(fn), subscriptionFlag(flag) {
		
		}
		Subscriber(std::function<void(Message)> fn, unsigned flag) : receivingFunction(fn){
			subscriptionFlag = static_cast<MessageType>(flag);
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
	void AddReceiver(MessageBusNode* receiver, unsigned subscriptionFlag);
	void AddReceiver(MessageBusNode* receiver, MessageType subscriptionFlag);
	void AddReceiver(MessageBusNode* receiver, std::vector<MessageType> flags);

	void RemoveReceiver(MessageBusNode* receiver);

	void PublishMessage(Message message);
	void DispatchMessages();


};

