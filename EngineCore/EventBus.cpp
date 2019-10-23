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
		while (!EventQueue.empty()) {
			auto event = EventQueue.front();
			auto eventCategory = static_cast<unsigned>(event->GetEventCategory());
			
			for (auto& listener : Listeners) {
				auto subscription = listener->GetSubscription();
				
				if ((subscription & eventCategory) != 0) {
					listener->ReceiveEvent(event);
				}
			}

			delete event;
			EventQueue.pop();
		}
	}

	void EventBus::AddListener(EventBusNode* node) {
		Listeners.insert(node);
	}
}