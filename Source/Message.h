#pragma once
//STD Headers
#include <string>

//Library Headers


//Forward Declarations

//Enumerations
enum MessageType {
	Initialization = 1,
	GenericEvent = 2,
	Error = 4,
	Termination = 8
};

class Message {
private:
	//Private class members
	std::string Event;
	MessageType Type;

public:
	Message(std::string message, MessageType type);
	~Message();

private:
	//Private member functions

public:
	//Public member functions
	std::string getEvent();
	MessageType getType();

};

