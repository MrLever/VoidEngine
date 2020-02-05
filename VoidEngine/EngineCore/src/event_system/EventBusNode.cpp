//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Logger.h"

#include "event_system/EventBusNode.h"
#include "event_system/EventBus.h"
#include "event_system/EventDispatcher.h"
#include "event_system/events/Event.h"

namespace core {

	EventBusNode::EventBusNode(EventBus* bus) : Bus(bus) {
		if (Bus) {
			Bus->AddListener(this);
		}
	}

	void EventBusNode::PublishEvent(Event* event) {
		if (Bus) {
			Bus->PostEvent(event);
		}
		else {
			utils::Logger::LogWarning("EventBusNode Failed to publish event");
		}
	}

	unsigned EventBusNode::GetSubscription() {
		//Default behavior is to not filter messages
		return -1; // = 0xFFFFF...
	}

}