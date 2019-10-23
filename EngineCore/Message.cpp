//STD Headers


//Library Headers


//Coati Headers
#include "Message.h"
#include "EngineUtilities.h"

namespace core {

	//CTORS

	Message::Message(const std::string &message, const MessageType &type) 
		: Event(message), Type(type) {

	}

	Message::Message(const std::string &message, unsigned type) 
		: Event(message), Type(static_cast<MessageType>(type)) {

	}


	Message::~Message() {
	}

	bool Message::operator==(const Message& other) const {
		return this->Event == other.Event;
	}

	utils::Name Message::GetEvent() const {
		return Event;
	}

	MessageType Message::GetType() const {
		return Type;
	}

	std::ostream& operator<<(std::ostream& out, const Message& message){
		return out << message.Event;
	}

}