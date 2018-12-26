//STD Headers
#include <memory>
#include <iostream>

//Library Headers


//Coati Headers
#include "MessageBusNode.h"
#include "MessageBus.h"
#include "Message.h"



MessageBusNode::MessageBusNode(std::shared_ptr<MessageBus> Bus) {
	this->GameMessageBus = Bus;

	if (!this->GameMessageBus) {
		std::cout << "no message bus";
	}
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

void MessageBusNode::PublishMessage(std::string message, MessageType type) {
	Message outgoing(message, type);
	GameMessageBus->PublishMessage(outgoing);
}

void MessageBusNode::PublishMessage(Message message) {
	GameMessageBus->PublishMessage(message);
}
