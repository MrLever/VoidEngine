//STD Headers
#include <iostream>

//Library Headers


//Coati Headers
#include "Message.h"
#include "EngineUtilities.h"
#include "EventTable.h"

namespace EngineCore {

	//CTORS

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

	bool EventTable::BindEvent(const Message &message, const std::function<void()> &action) {
		Events.insert({ message, action });
		return true;
	}

	bool EventTable::UnbindEvent(const Message &message) {
		return Events.erase(message) > 0;
	}

}