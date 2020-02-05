#pragma once
//STD Headers
#include <concepts>
#include <type_traits>

//Library Headers

//Void Engine Headers
#include "core/event_system/events/Event.h"

namespace core {
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
		template<class T, class F> /*requires std::derived_from<F, T>*/ 
		bool Dispatch(const F&& callback);
		 
	private:
		Event* PendingEvent;

	};

	template<class T, class F> /*requires std::derived_from<F, T>*/
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
