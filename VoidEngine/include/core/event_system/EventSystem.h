#pragma once
//STD Headers
#include <functional>
#include <forward_list>
#include <unordered_map>
#include <unordered_set>

//Library Headers

//Void Engine Headers
#include "core/event_system/Event.h"

namespace core {
	class EventSystem;
	class EventListener;

	class EventListener {
	public:
		/**
		 * Constructor
		 */
		EventListener(EventSystem* eventSystem);

		/**
		 * Destructor
		 * Implicitly unregisters this listener from ALL event types
		 */
		~EventListener();

		/**
		 * Allows user to register a callback to an event through this listener
		 * @param callback The code to be executed when the event is triggered
		 */
		template<class T>
		void SubscribeToEvent(const std::function<void(T*)>& callback);

		/**
		 * Allows user to clear all event subscriptions
		 */
		void ClearSubscriptions();

		/**
		 * Allows user to unregister a callback through this listener
		 */
		template<class T>
		void UnsubscribeFromEvent();

		/**
		 * Allows user to post event through this listener
		 * @param event the event to send to the event queue
		 * @note event system will take ownership of the event's lifetime
		 */
		void PostEvent(std::unique_ptr<Event> event);

		template <class T, typename ...Args>
		void PostEvent(Args&&... args);

	private:
		EventSystem* eventSystem;
	};

	class EventSystem {
	public:
		/**
		 * Constructor
		 */
		EventSystem();

		/**
		 * Destructor
		 */
		~EventSystem();
	
		/**
		 * Submits an event to the event systems and takes ownership of event lifetime
		 */
		void PostEvent(std::unique_ptr<Event> event);

		/**
		 * Flushes the event queue and sends events to listeners
		 */
		void DispatchEvents();

		/**
		 * Registers event listener for event type T
		 * @tparam T the type of event being registered for (T allows the use of more wreckless casts)
		 * @param listener the listener to register
		 * @param callback the callback to register
		 */
		template<class T>
		void RegisterListener(EventListener* listener, const std::function<void(T*)>& callback);

		/**
		 * Unregisters an event listener from ALL event dispatchers
		 * @param listener the event listener to unregister
		 */
		void DeregisterListener(EventListener* listener);

		/**
		 * Registers event listener for event type T
		 * @tparam T the type of event being registered for (T allows the use of more wreckless casts)
		 * @param listener the listener to register
		 * @param callback the callback to register
		 */
		template<class T>
		void DeregisterListenerFromEvent(EventListener* listener);

	private:
		using EventCallbackWrapper = std::function<void(Event*)>;

		struct EventRegistration {
			EventListener* listener;
			EventCallbackWrapper callback;

			bool operator==(const EventRegistration& other) const;
		};

		//Hashing functor for event registrations
		struct EventRegistrationHash {
			std::size_t operator()(const EventRegistration& reg) const;
		};

		/** Master map of Event type to subscribed listeners */
		std::unordered_map<
			EventID, 
			std::unordered_set<EventRegistration, EventRegistrationHash>
		> eventDirectory;

		std::list<std::unique_ptr<Event>> eventQueue;

	};

	///////////////////////////////////////////////////////////////////////////
	//// Event System Impl
	///////////////////////////////////////////////////////////////////////////

	template<class T>
	inline void EventSystem::RegisterListener(EventListener* listener, const std::function<void(T*)>& callback) {
		//Get event registration type
		auto id = T::GetStaticTypename().ID;
		
		//Wrap callback function in a generic wrapper for storage
		auto wrappedCallback = [callback](Event* baseEvent) {
			//Perform static cast using type provided in registration
			//This preserves type safety of the event system because I'm a fuckin genius
			T* event = static_cast<T*>(baseEvent);
			callback(event);
		};
		
		//Insert into callback set for the selected event type 
		eventDirectory[id].insert({ listener, wrappedCallback });
	}

	template<class T>
	inline void EventSystem::DeregisterListenerFromEvent(EventListener* listener) {
		auto id = T::GetStaticTypename().ID;
		EventRegistration dummyReg{ listener };
		eventDirectory[id].erase(dummyReg);
	}

	///////////////////////////////////////////////////////////////////////////
	//// Event Listener Impl
	///////////////////////////////////////////////////////////////////////////

	template<class T>
	inline void EventListener::SubscribeToEvent(const std::function<void(T*)>& callback) {
		eventSystem->RegisterListener<T>(this, callback);
	}

	template<class T>
	inline void EventListener::UnsubscribeFromEvent() {
		eventSystem->DeregisterListenerFromEvent<T>(this);
	}

	template<class T, typename ...Args>
	inline void EventListener::PostEvent(Args&& ...args) {
		auto event = std::make_unique<T>(std::forward<Args>(args)...);
		eventSystem->PostEvent(std::move(event));
	}
}