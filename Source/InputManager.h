#pragma once
//STD Headers
#include <memory>
#include <unordered_map>

//Library Headers

//Coati Headers
#include "MessageBusNode.h"
#include "KeyboardInput.h"

//Forward Class declarations
class MessageBus;
class InputEvent;


class InputManager : MessageBusNode {
private:
	//Private class members
	std::unordered_map<KeyType, Message> Keybindings;

public:
	//CTORS
	InputManager(std::shared_ptr<MessageBus> GameMessageBus);
	~InputManager();

private:
	//Private member functions
	void LoadKeybindings();

public:
	//Public member functions
	void HandleInput(KeyboardInput input);

	virtual void RegisterReciever() override;
	virtual void ReceiveMessage(Message message);
};

