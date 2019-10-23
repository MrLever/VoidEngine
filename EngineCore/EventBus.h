#pragma once
//STD Headers
#include <queue>

//Library Headers

//Void Engine Headers
#include "Event.h"

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

	private:
		/** Queue of unprocessed events */
		std::queue<Event*> EventQueue;
	};

}

using EventBusPtr = std::shared_ptr<core::EventBus>;