//STD Headers


//Library Headers


//Coati Headers
#include "Message.h"
#include "EngineUtilities.h"

namespace EngineCore {

	//CTORS

	Message::Message(std::string message, MessageType type) : Event(message), Type(type) {
		this->ID = EngineUtilities::FNV1aHash(message);
	}

	Message::Message(std::string message, unsigned type) :
		Event(message),
		Type(static_cast<MessageType>(type))
	{
		this->ID = EngineUtilities::FNV1aHash(message);
	}


	Message::~Message() {
	}

	bool Message::operator==(const Message& other) const {
		return this->ID == other.ID;
	}

	std::string Message::GetEvent() const {
		return Event;
	}

	unsigned Message::GetEventID() const {
		return ID;
	}

	MessageType Message::GetType() const {
		return Type;
	}

	//Private Functions


	//Public Functions

}