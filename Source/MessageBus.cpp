//STD Headers
#include <functional>
#include <queue>
#include <vector>

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
void MessageBus::AddReciever(MessageBusNode* receiver, int subscriptionFlag) {
	
	Subscriber subscriber(receiver->GetMessageReceiveFunction(), subscriptionFlag);
	Receivers.push_back(subscriber);
}

void MessageBus::PublishMessage(Message message) {
	Messages.push(message);
}

void MessageBus::DispatchMessages() {
	while (!Messages.empty()) {
		Message outgoingMessage = Messages.front();
		for (auto receiver : Receivers) {
			if (receiver.subscriptionFlag & outgoingMessage.getType()) {
				receiver.receivingFunction(Messages.front());
			}
			
			//(*i)(Messages.front());
		}
		Messages.pop();
	}
}

