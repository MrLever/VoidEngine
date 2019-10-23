#pragma once

//STD Headers
#include <functional>
#include <queue>
#include <vector>
#include <utility>

//Library Headers

//Coati Headers
#include "Message.h"
#include "MessageBusNode.h"

namespace core {
	/**
	 * @class MessageBus Class to handle message propogation in the game world
	 */
	class MessageBus {

		/**
		 * Struct to store subscribes and their subscription flags 
		 */
		struct Subscriber {
			MessageBusNode* Receiver;
			MessageType SubscriptionFlag;

			Subscriber(MessageBusNode* receiver, MessageType flag) 
				: Receiver(std::move(receiver)), SubscriptionFlag(flag) {

			}

			Subscriber(MessageBusNode* receiver, unsigned flag) : Receiver(std::move(receiver)) {
				SubscriptionFlag = static_cast<MessageType>(flag);
			}

			void Send(const Message& message) const {
				if (Receiver) {
					Receiver->ReceiveMessage(message);
				}
			}
		};

	public:
		/**
		 * Constructor
		 */
		MessageBus() = default;

		/**
		 * Destructor
		 * Dispatches all pending log messages to std::out
		 */
		~MessageBus();

		/**
		 * Adds a receiver to the distribution list
		 * @param receiver the message receiver
		 * @param subscriptionFlag the receiver's subscription flag to filter unwanted messages
		 */
		void AddReceiver(MessageBusNode* receiver, unsigned subscriptionFlag);

		/**
		 * Adds a receiver to the distribution list
		 * @param receiver the message receiver
		 * @param subscriptionFlag the receiver's subscription flag to filter unwanted messages
		 */
		void AddReceiver(MessageBusNode* receiver, MessageType subscriptionFlag);

		/**
		 * Adds a receiver to the distribution list
		 * @param receiver the message receiver
		 * @param subscriptionFlag the receiver's subscription flag to filter unwanted messages
		 */
		void AddReceiver(MessageBusNode* receiver, const std::vector<MessageType> &flags);

		/**
		 * Removes a MessageBusNode from the distribution list
		 * @param receiver The Node to unregister
		 */
		void RemoveReceiver(MessageBusNode* receiver);

		/**
		 * Adds a message to be distributed on the next call to DispatchMessages
		 * @param message The message to distribute
		 */
		void PublishMessage(const Message &message);

		/**
		 * Sends queued messages to receivers
		 */
		void DispatchMessages();

	private:
		/** FIFO queue of messages to distribute */
		std::queue<Message> Messages;

		/** List of subscribers to send messages to */
		std::vector<Subscriber> Receivers;
	};

}