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
class WindowManager;
class InputEvent;


class InputManager : MessageBusNode {
private:
	//Private class members
	std::shared_ptr<WindowManager> Window;
	std::unordered_map<KeyType, Message> Keybindings;

public:
	//CTORS
	InputManager(std::shared_ptr<MessageBus> GameMessageBus, std::shared_ptr<WindowManager> Window);
	~InputManager();

public:
	//Public member functions
	void PollInput();
	void HandleInput(KeyboardInput input);

	virtual void RegisterReciever() override;
	virtual void ReceiveMessage(Message message);
};

