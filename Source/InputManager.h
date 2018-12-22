#pragma once
//STD Headers
#include <memory>

//Library Headers


//Forward Class declarations
class MessageBus;
class WindowManager;

class InputManager {
private:
	//Private class members
	std::shared_ptr<MessageBus> GameMessageBus;
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
};

