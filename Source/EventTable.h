#pragma once

//STD Headers
#include <unordered_map>
#include <functional>

//Library Headers

//Coati Headers

//Forward Class declarations


class EventTable{
private:
	//Private Class Members
	std::unordered_map<Message, std::function<void()>> Events;

public:
	//CTORS
	EventTable();
	~EventTable();

	std::function<void()> operator[] (const Message& event) const;


private:
	//Private member functions

public:
	//Public member functions
	bool BindEvent(Message message, std::function<void()> event);
	bool UnbindEvent(Message message);
};

