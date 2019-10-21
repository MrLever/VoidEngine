#pragma once
//STD Headers
#include <chrono>
#include <memory>
#include <functional>
#include <string>
#include <unordered_map>

//Library Headers

//Coati Headers
#include "Message.h"
#include "EventTable.h"

namespace core {

	//Forward Class declarations
	class MessageBus;

	/**
	 * @class MessageBusNode
	 * @brief Class to provide an interface for entities to send and receive messages
	 *        on the provided message bus
	 */
	class MessageBusNode {
	public:
		/**
		 * Constructor
		 * @param messageBus The MessageBus this node interacts with
		 */
		MessageBusNode(MessageBus* messageBus);

		/**
		 * Destructor
		 */
		~MessageBusNode();

		/**
		 * Function that allows message bus nodes to receive transmissions from the MessageBus
		 * @param message The incomming message
		 */
		virtual void ReceiveMessage(const Message& message);

	protected:

		/**
		 * Method to register a receiver as a subscriber to the message bus
		 */
		virtual void RegisterReciever();

		/**
		 * Method to unregister a receiver on the message bus
		 */
		virtual void UnregisterReciever();

		/**
		 * Pure virtual function that allows derived classed to specify how they will react to
		 * certain messages
		 */
		virtual void RegisterEvents() = 0;

		/**
		 * Constructs and publishes a message to the message bus
		 * @param message The Message's body
		 * @param type The Message's type
		 */
		void PublishMessage(const std::string &message, const MessageType &type);
		
		/**
		 * Sends a message to the message bus for distribution
		 * @param message The message to send
		 */
		void PublishMessage(const Message &message);

		/** Pointer to the MessageBus this node interacts with */
		MessageBus* Bus;

		/** Data structure to manage message processing */
		EventTable Events;
	};

}