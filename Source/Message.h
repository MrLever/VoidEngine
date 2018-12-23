#pragma once
//STD Headers
#include <string>

//Library Headers


//Forward Declarations
class Message {
private:
	//Private class members
	std::string Event;

public:
	Message(std::string message);
	~Message();

private:
	//Private member functions

public:
	//Public member functions
	std::string getEvent();

};

