//STD Headers
#include <memory>
#include <iostream>

//Library Headers


//Coati Headers
#include "MessageBusNode.h"
#include "MessageBus.h"
#include "Message.h"
#include "EventTable.h"

namespace EngineCore {

	MessageBusNode::MessageBusNode(std::shared_ptr<MessageBus> Bus) : GameMessageBus(std::move(Bus)) {

		if (!this->GameMessageBus) {
			std::cout << "no message bus";
		}
	}

	MessageBusNode::~MessageBusNode() {
		UnregisterReciever();
	}

	// Protected Member Functions

	void MessageBusNode::RegisterReciever() {
		GameMessageBus->AddReceiver(this, MessageType::DebugIgnore);
	}

	void MessageBusNode::UnregisterReciever() {
		GameMessageBus->RemoveReceiver(this);
	}

	void MessageBusNode::PublishMessage(const std::string &message, const MessageType &type) {
		Message outgoing(message, type);
		GameMessageBus->PublishMessage(outgoing);
	}

	void MessageBusNode::PublishMessage(const Message &message) {
		GameMessageBus->PublishMessage(message);
	}

	// Public Member Functions

	std::function<void(Message)>MessageBusNode::GetMessageReceiveFunction() {
		auto receiveFunction = [=](const Message &message) -> void {
			this->ReceiveMessage(message);
		};
		return receiveFunction;
	}

}