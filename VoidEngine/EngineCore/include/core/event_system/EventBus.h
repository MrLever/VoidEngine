#pragma once
//STD Headers
#include <queue>
#include <unordered_set>

//Library Headers

//Void Engine Headers
#include "core/event_system/events/Event.h"
#include "core/event_system/EventBusNode.h"

namespace core {
	class EventBus {
	public:
		/**
		 * Constructor
		 */
		EventBus() = default;
		
		/**
		 * Destructor
		 */
		~EventBus();

		/**
		 * Function to allow events to be posted to the bus.
		 * @note The Event Bus takes ownership of the event pointer past this call.
		 * @param event The event being reported
		 */
		void PostEvent(Event* event);

		/**
		 * Instructs the EventBus to dispatch events into the engine.
		 * @note Events are freed from the heap after they are dispatched
		 */
		void DispatchEvents();

		/**
		 * Adds EventBusNode to the subscriber pool
		 * @param node The node to add
		 */
		void AddListener(EventBusNode* node);

	private:
		/** Queue of unprocessed events */
		std::queue<Event*> EventQueue;

		/** Set of listeners for this bus */
		std::unordered_set<EventBusNode*> Listeners;
	};

}

using EventBusPtr = std::shared_ptr<core::EventBus>;