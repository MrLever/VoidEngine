#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "core/event_system/EventDispatcher.h"

namespace core {
	//Forward Class Declarations
	class EventBus;
	class Event;

	/**
	 * @class EventBusNode
	 * @brief An EventBusNode is any object that is capable of sending 
	 *        or receiving events
	 */
	class EventBusNode {
	public:
		/**
		 * Constructor
		 */
		EventBusNode(EventBus* bus);

		/**
		 * Allows nodes to publish events to the EventBus
		 * @param event The event to publish
		 */
		virtual void PublishEvent(Event* event) final;

		/**
		 * Allows node to receive and process events from EventBus
		 * @param event The event to process
		 */
		virtual void ReceiveEvent(Event* event) = 0;

		/**
		 * Allows EventBus to query the node's subscription, and filter events accordingly
		 */
		virtual unsigned GetSubscription();

	protected:
		/** The event bus this node communicates with */
		EventBus* Bus;
	};

}
