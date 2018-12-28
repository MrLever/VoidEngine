#pragma once
//STD Headers
#include <unordered_map>
#include <string>

//Library Headers

//Coati Headers
#include "KeyboardInput.h"
#include "Serializable.h"

//Forward Class declarations
class Message;

class Keybindings : Serializable {
private:
	//Private Class Members

	//Third template parameter required to inform map how to custom key type
	std::unordered_map<KeyboardInput, Message> Bindings;

public:
	//CTORS
	Keybindings();
	~Keybindings();

private:
	//Private Member Functions

public:
	//Public Member Functions
	void AddBinding(KeyboardInput input, std::string event, int eventType);
	void RemoveBinding(KeyboardInput key);
	void ReassignBinding(KeyboardInput key, std::string event, int EventType);

	Message GetBinding(KeyboardInput input);

	virtual void Save() override;
	virtual void Load() override;
};

