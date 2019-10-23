#pragma once
//STD Headers
#include <concepts>
#include <type_traits>
//Library Headers

//Void Engine Headers
#include "Event.h"

namespace core {
	template<typename T>
	concept IsEvent = requires { std::is_base_of<Event, T>::value; };

	/**
	 * @class EventDispatcher
	 * @brief The EventDispatcher is helper class that accepts an event
	 */
	class EventDispatcher {
	public:
		/**
		 * Constructor
		 * @param event The event to dispatch
		 */
		EventDispatcher(Event* event);

		/**
		 * Function to help EventBusNodes dispatch the events recieve to the appropriate callback function
		 * @param callback The function to call should the event be dispatched
		 * @tparam T The type of event for which callback should be executed
		 * @tparam F The type of the callback (should be deduced by compiler)
		 */
		template<class T, class F> /* requires IsEvent<T> */
		bool Dispatch(const F&& callback);
		 
	private:
		Event* PendingEvent;

	};

	template<class T, class F> /* requires IsEvent<T> */
	bool EventDispatcher::Dispatch(const F&& callback) {
		if (PendingEvent->GetEventType() == T::GetStaticEventType()) {
			callback(static_cast<T*>(PendingEvent));
			return true;
		}
		else {
			return false;
		}
	}

}
