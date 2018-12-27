#pragma once
//STD Headers
#include <unordered_map>

//Library Headers

//Coati Headers
#include "KeyboardInput.h"

//Forward Class declarations
class Message;

class Keybindings {
private:
	//Priavet Class Members
	std::unordered_map<KeyType, Message> Bindings;

public:
	//CTORS
	Keybindings();
	~Keybindings();

private:
	//Private Member Functions

public:
	//Public Member Functions
	void AddBinding();
	void RemoveBinding();
	void ReassignBinding();
};

