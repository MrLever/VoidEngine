//STD Headers
#include <memory>

//Library Headers


//Coati Headers
#include "MessageBusNode.h"
#include "MessageBus.h"
#include "Message.h"



MessageBusNode::MessageBusNode(std::shared_ptr<MessageBus> GameMessageBus) {
	this->GameMessageBus = GameMessageBus;
}


MessageBusNode::~MessageBusNode() {

}

std::function<void(Message)>MessageBusNode::GetMessageReceiveFunction() {
	auto receiveFunction = [=](Message message) -> void {
		this->ReceiveMessage(message);
	};
	return receiveFunction;
}

void MessageBusNode::RegisterReciever() {
	this->GameMessageBus->AddReciever(this, Initialization);
}