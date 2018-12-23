//STD Headers


//Library Headers


//Coati Headers
#include "Message.h"


//CTORS

Message::Message(std::string message) : Event(message){

}


Message::~Message() {
}

std::string Message::getEvent() {
	return Event;
}

//Private Functions


//Public Functions

