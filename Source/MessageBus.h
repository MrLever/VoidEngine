#pragma once

//STD Headers
#include <functional>
#include <queue>
#include <vector>
#include <utility>

//Library Headers

//Coati Headers
#include "Message.h"

namespace EngineCore {

	//Forward Class declarations
	class MessageBusNode;

	class MessageBus {

		struct Subscriber {
			std::function<void(Message)> receivingFunction;
			MessageType subscriptionFlag;

			Subscriber(std::function<void(Message)> fn, MessageType flag) : receivingFunction(std::move(fn)), subscriptionFlag(flag) {

			}

			Subscriber(std::function<void(Message)> fn, unsigned flag) : receivingFunction(std::move(fn)) {
				subscriptionFlag = static_cast<MessageType>(flag);
			}
		};

	private:
		//Private Class members
		std::queue<Message> Messages;
		std::vector<Subscriber> Receivers;

	public:
		MessageBus() = default;
		~MessageBus() = default;

	private:
		//Private member functions

	public:
		void AddReceiver(MessageBusNode* receiver, unsigned subscriptionFlag);
		void AddReceiver(MessageBusNode* receiver, MessageType subscriptionFlag);
		void AddReceiver(MessageBusNode* receiver, std::vector<MessageType> flags);

		void RemoveReceiver(MessageBusNode* receiver);

		void PublishMessage(Message message);
		void DispatchMessages();


	};

}