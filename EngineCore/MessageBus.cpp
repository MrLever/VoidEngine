//STD Headers
#include <functional>
#include <queue>
#include <vector>
#include <iostream>

//Library Headers

//Coati Headers
#include "MessageBus.h"
#include "MessageBusNode.h"
#include "Message.h"

namespace core {
	
	MessageBus::~MessageBus() {
		while (!Messages.empty()) {
			auto currMsg = Messages.front();
			if (currMsg.GetType() == MessageType::Log) {
				std::cout << currMsg;
			}
			Messages.pop();
		}
	}
	
	void MessageBus::AddReceiver(MessageBusNode* receiver, unsigned subscriptionFlag) {
		Receivers.push_back(Subscriber(receiver, subscriptionFlag));
	}

	void MessageBus::AddReceiver(MessageBusNode* receiver, MessageType subscriptionFlag) {
		AddReceiver(receiver, static_cast<unsigned>(subscriptionFlag));
	}

	void MessageBus::AddReceiver(MessageBusNode* receiver, const std::vector<MessageType> &flags) {
		//Bitwise OR all of the flags together to make a super flag
		unsigned flag = 0;
		for (auto inputFlag : flags) {
			flag |= static_cast<unsigned>(inputFlag);
		}
		
		AddReceiver(receiver, flag);
	}

	void MessageBus::RemoveReceiver(MessageBusNode* receiver) {

	}

	void MessageBus::PublishMessage(const Message &message) {
		Messages.push(message);
	}

	void MessageBus::DispatchMessages() {
		while (!Messages.empty()) {
			Message outgoingMessage = Messages.front();
			for (const auto &receiver : Receivers) {
				auto subsription = static_cast<unsigned>(receiver.SubscriptionFlag);
				auto messageType = static_cast<unsigned>(outgoingMessage.GetType());
				if ((subsription & messageType) != 0) {
					receiver.Send(Messages.front());
				}
			}
			Messages.pop();
		}
	}

}