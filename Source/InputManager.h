#pragma once
//STD Headers
#include <memory>

//Library Headers

//Coati Headers
#include "MessageBusNode.h"

//Forward Class declarations
class MessageBus;
class WindowManager;

class InputManager : MessageBusNode {
private:
	//Private class members
	std::shared_ptr<WindowManager> Window;

public:
	//CTORS
	InputManager(std::shared_ptr<MessageBus> GameMessageBus, std::shared_ptr<WindowManager> Window);
	~InputManager();

private:
	//Private member functions

public:
	//Public member functions
	void PollInput();

	virtual void RegisterReciever() override;
	virtual void ReceiveMessage(Message message);
};

