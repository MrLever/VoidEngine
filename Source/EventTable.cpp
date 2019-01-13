//STD Headers
#include <iostream>

//Library Headers


//Coati Headers
#include "Message.h"
#include "EngineUtilities.h"
#include "EventTable.h"

//CTORS

EventTable::EventTable() {
}


EventTable::~EventTable() {
}

std::function<void()> EventTable::operator[](const Message& event) const {
	
	auto lookup = Events.find(event);
	
	//If the event is not found, return an empty function
	if (lookup == Events.end()) {
		return nullptr;
	}

	return Events.find(event)->second;
}



//Private Member Functions

//Protected Member Functions

//Public Member Functions

void EventTable::BindEvent(Message message, std::function<void()> event) {
	Events.insert({ message, event });
}

void EventTable::UnbindEvent(Message message) {
	Events.erase(message);
}
