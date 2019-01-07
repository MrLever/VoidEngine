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

MessageBus::MessageBus(){
}


MessageBus::~MessageBus(){

}

//Private Member Functions

//Public Member Functions
void MessageBus::AddReceiver(MessageBusNode* receiver, unsigned subscriptionFlag) {
	
	Subscriber subscriber(receiver->GetMessageReceiveFunction(), subscriptionFlag);
	Receivers.push_back(subscriber);
}

void MessageBus::AddReceiver(MessageBusNode * receiver, MessageType subscriptionFlag) {
	AddReceiver(receiver, static_cast<unsigned>(subscriptionFlag));
}

void MessageBus::AddReceiver(MessageBusNode* receiver, std::vector<MessageType> flags) {
	unsigned flag = 0;
	for (auto inputFlag : flags) {
		flag |= static_cast<unsigned>(inputFlag);
	}
	AddReceiver(receiver, flag);
}

void MessageBus::PublishMessage(Message message) {
	Messages.push(message);
}

void MessageBus::DispatchMessages() {
	while (!Messages.empty()) {
		Message outgoingMessage = Messages.front();
		for (auto receiver : Receivers) {
			unsigned subsription = static_cast<unsigned>(receiver.subscriptionFlag);
			unsigned messageType = static_cast<unsigned>(outgoingMessage.GetType());
			if (subsription & messageType) {
				receiver.receivingFunction(Messages.front());
			}
		}
		Messages.pop();
	}
}

