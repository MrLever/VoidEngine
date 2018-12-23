//STD Headers
#include <functional>
#include <queue>
#include <vector>

//Library Headers


//Coati Headers
#include "MessageBus.h"
#include "Message.h"

MessageBus::MessageBus(){
}


MessageBus::~MessageBus(){

}

//Private Member Functions

//Public Member Functions
void MessageBus::AddReciever(std::function<void(Message)> subsriber) {
	Recievers.push_back(subsriber);
}

void MessageBus::PublishMessage(Message message) {
	Messages.push(message);
}

void MessageBus::DispatchMessages() {
	while (!Messages.empty()) {
		for (auto i = Recievers.begin(); i != Recievers.end(); i++) {
			(*i)(Messages.front());
		}
		Messages.pop();
	}
}

