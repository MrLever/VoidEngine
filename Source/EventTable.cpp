//STD Headers
#include <iostream>

//Library Headers


//Coati Headers
#include "Message.h"
#include "EngineUtilities.h"
#include "EventTable.h"

namespace EngineCore {

	//CTORS

	EventTable::EventTable() {
	}


	EventTable::~EventTable() {
	}

	//Operator Overloads
	std::function<void()> EventTable::operator[](const Message& event) const {

		auto lookup = Events.find(event);

		//If the event is not found, return an empty function pointer
		if (lookup == Events.end()) {
			return nullptr;
		}

		return Events.find(event)->second;
	}



	//Private Member Functions

	//Protected Member Functions

	//Public Member Functions

	bool EventTable::BindEvent(Message message, std::function<void()> event) {
		Events.insert({ message, event });
		return true;
	}

	bool EventTable::UnbindEvent(Message message) {
		if (Events.erase(message) > 0) {
			return true;
		}

		return false;
	}

}