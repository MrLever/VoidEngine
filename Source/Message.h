#pragma once
//STD Headers
#include <string>

//Library Headers


//Forward Declarations

enum class MessageType : unsigned {
	Initialization = 1,
	Input		   = 2,
	GenericEvent   = 4,
	Error		   = 8,
	Termination	   = 16
};


class Message {

private:
	//Private class members
	std::string Event;
	MessageType Type;

public:
	Message(std::string message, MessageType type);
	Message(std::string message, int type);
	~Message();

private:
	//Private member functions

public:
	//Public member functions
	std::string getEvent();
	MessageType getType();

};

