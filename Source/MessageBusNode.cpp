//STD Headers
#include <memory>
#include <iostream>

//Library Headers


//Coati Headers
#include "MessageBusNode.h"
#include "MessageBus.h"
#include "Message.h"
#include "EventTable.h"



MessageBusNode::MessageBusNode(std::shared_ptr<MessageBus> Bus) {
	this->GameMessageBus = Bus;

	if (!this->GameMessageBus) {
		std::cout << "no message bus";
	}
}

MessageBusNode::~MessageBusNode() {
	UnregisterReciever();
}

// Protected Member Functions

void MessageBusNode::RegisterReciever() {
	GameMessageBus->AddReceiver(this, 0xFFFFFFFF);
}

void MessageBusNode::UnregisterReciever() {
	GameMessageBus->RemoveReceiver(this);
}

void MessageBusNode::PublishMessage(std::string message, MessageType type) {
	Message outgoing(message, type);
	GameMessageBus->PublishMessage(outgoing);
}

void MessageBusNode::PublishMessage(Message message) {
	GameMessageBus->PublishMessage(message);
}

// Public Member Functions

std::function<void(Message)>MessageBusNode::GetMessageReceiveFunction() {
	auto receiveFunction = [=](Message message) -> void {
		this->ReceiveMessage(message);
	};
	return receiveFunction;
}