//STD Headers

//Library Headers

//Void Engine Headers
#include "EventBus.h"

namespace core {
	EventBus::~EventBus() {
		while (!EventQueue.empty()) {
			delete EventQueue.front();
			EventQueue.pop();
		}
	}

	void EventBus::PostEvent(Event* event) {
		EventQueue.push(event);
	}

	void EventBus::DispatchEvents() {
	
	}
}