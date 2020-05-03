//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Logger.h"
#include "event_system/EventSystem.h"

namespace core {
	///////////////////////////////////////////////////////////////////////////
	//// Event System Impl
	///////////////////////////////////////////////////////////////////////////

	void EventSystem::PostEvent(std::unique_ptr<Event> event) {
		eventQueue.emplace_back(std::move(event));
	}

	void EventSystem::DispatchEvents() {
		while (eventQueue.size() > 0) {
			//Get current event to dispatch
			auto event = eventQueue.front().get();
			
			//Get event's id
			auto id = event->GetTypename().ID;

			//Get set of listeners subscribed to the ID
			auto& callbackSet = eventDirectory[id];

			//Dispatch
			for (auto& registration : callbackSet) {
				registration.callback(event);
			}

			//Discard event
			eventQueue.pop_front();
		}
	}

	void EventSystem::UnregisterListener(EventListener* listener) {
		for (auto& directoryEntry : eventDirectory) {
			auto& set = directoryEntry.second;
			EventRegistration dummyReg{ listener };
			set.erase(dummyReg);
		}
	}
	
	bool EventSystem::EventRegistration::operator==(const EventRegistration& other) const {
		return listener == other.listener;
	}

	std::size_t EventSystem::EventRegistrationHash::operator()(const EventRegistration& reg) const {
		//Hash by pointer address of listener
		return (std::size_t)reg.listener;
	}

	///////////////////////////////////////////////////////////////////////////
	//// Event Listener Impl
	///////////////////////////////////////////////////////////////////////////

	EventListener::EventListener(EventSystem* eventSystem) : eventSystem(eventSystem) {

	}

	EventListener::~EventListener() {
		eventSystem->UnregisterListener(this);
	}

	void EventListener::PostEvent(Event* event) {
		eventSystem->PostEvent(std::unique_ptr<Event>(event));
	}
}