//STD Headers
#include <memory>

//Library Headers


//Coati Headers
#include "MessageBusNode.h"
#include "MessageBus.h"
#include "Message.h"
#include "EventTable.h"
#include "Logger.h"

namespace core {

	MessageBusNode::MessageBusNode(MessageBus* messageBus) 
		: Bus(std::move(messageBus)) {

		if (!Bus) {
			utils::Logger::LogWarning("Invalid MessageBus supplied to MessageBusNode");
		}
	}

	MessageBusNode::~MessageBusNode() {
		UnregisterReciever();
	}

	void MessageBusNode::RegisterReciever() {
		Bus->AddReceiver(this, MessageType::NACK);
	}

	void MessageBusNode::UnregisterReciever() {
		Bus->RemoveReceiver(this);
	}

	void MessageBusNode::PublishMessage(const std::string &message, const MessageType &type) {
		Message outgoing(message, type);
		Bus->PublishMessage(outgoing);
	}

	void MessageBusNode::PublishMessage(const Message &message) {
		Bus->PublishMessage(message);
	}

	void MessageBusNode::ReceiveMessage(const Message& message) {
		if (Events[message]) {
			Events[message]();
		}
	}

}