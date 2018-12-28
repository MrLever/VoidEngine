//STD Headers


//Library Headers


//Coati Headers
#include "Message.h"


//CTORS

Message::Message(std::string message, MessageType type) : Event(message), Type(type) {

}

Message::Message(std::string message, int type) : 
	Event(message), 
	Type(static_cast<MessageType>(type)) 
{

}


Message::~Message() {
}

std::string Message::getEvent() {
	return Event;
}

MessageType Message::getType() {
	return Type;
}

//Private Functions


//Public Functions

