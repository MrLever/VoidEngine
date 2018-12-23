//STD Headers
#include <memory>

//Library Headers


//Coati Headers
#include "MessageBusNode.h"
#include "MessageBus.h"
#include "Message.h"



MessageBusNode::MessageBusNode(std::shared_ptr<MessageBus> GameMessageBus) {
	this->GameMessageBus = GameMessageBus;
	this->GameMessageBus->AddReciever(this->GetMessageReceiveFunction());
}


MessageBusNode::~MessageBusNode() {
}

std::function<void(Message)>MessageBusNode::GetMessageReceiveFunction() {
	auto messageListener = [=](Message message) -> void {
		this->ReceiveMessage(message);
	};
	return messageListener;
}