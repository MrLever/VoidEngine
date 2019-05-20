//STD Headers


//Library Headers


//Coati Headers
#include "Message.h"
#include "EngineUtilities.h"

namespace EngineCore {

	//CTORS

	Message::Message(const std::string &message, const MessageType &type) : Event(message), Type(type) {
		this->ID = EngineUtilities::FNV1aHash(message);
	}

	Message::Message(const std::string &message, unsigned type) 
		: Event(message), Type(static_cast<MessageType>(type))
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

	unsigned long long Message::GetEventID() const {
		return ID;
	}

	MessageType Message::GetType() const {
		return Type;
	}

	//Private Functions


	//Public Functions

}