#pragma once
//STD Headers
#include <chrono>
#include <memory>
#include <functional>
#include <string>

//Library Headers

//Coati Headers
#include "Message.h"

//Forward Class declarations
class MessageBus;


class MessageBusNode {
private:
	//Private Class Members
	

protected:
	//Protected Class Members
	std::shared_ptr<MessageBus> GameMessageBus;

public:
	//CTORS
	MessageBusNode(std::shared_ptr<MessageBus> GameMessageBus);
	~MessageBusNode();

private:
	//Privatate Member Functions

protected:
	//Protected Member Functions
	virtual void RegisterReciever();
	void PublishMessage(std::string, MessageType type);

public:
	//Public Member Functions
	std::function<void(Message)> GetMessageReceiveFunction();
	virtual void ReceiveMessage(Message message) = 0;

};

