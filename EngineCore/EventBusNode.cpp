//STD Headers

//Library Headers

//Void Engine Headers
#include "EventBusNode.h"
#include "Event.h"
#include "EventBus.h"
#include "EventDispatcher.h"
#include "Logger.h"

namespace core {

	EventBusNode::EventBusNode(EventBus* bus) : Bus(bus) {
	
	}

	void EventBusNode::PublishEvent(Event* event) {
		if (Bus) {
			Bus->PostEvent(event);
		}
		else {
			utils::Logger::LogWarning("EventBusNode Failed to publish event");
		}
	}

}