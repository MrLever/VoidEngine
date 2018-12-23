#pragma once
//STD Headers
#include <chrono>
#include <memory>
#include <functional>

//Library Headers


//Forward Class declarations
class MessageBus;
class Message;

class MessageBusNode {
private:
	//Private Class Members
	std::shared_ptr<MessageBus> GameMessageBus;
protected:
	//Protected Class Members

public:
	MessageBusNode(std::shared_ptr<MessageBus> GameMessageBus);
	~MessageBusNode();

private:
	//Privatate Member Functions

protected:
	//Protected Member Functions
	std::function<void(Message)> GetMessageReceiveFunction();


public:
	//Public Member Functions
	virtual void ReceiveMessage(Message message) = 0;
};

