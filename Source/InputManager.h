#pragma once
//STD Headers
#include <memory>
#include <unordered_map>
#include <unordered_set>

//Library Headers

//Coati Headers
#include "MessageBusNode.h"
#include "KeyboardInput.h"
#include "Keybindings.h"

namespace EngineCore {

	//Forward Class declarations
	class MessageBus;
	class InputEvent;


	class InputManager : MessageBusNode {
	private:
		//Private class members
		Keybindings Bindings;

	public:
		//CTORS
		InputManager(std::shared_ptr<MessageBus> GameMessageBus);
		~InputManager();

	private:
		virtual void RegisterReciever() override;
		void RegisterEvents() override;

		//Private member functions
		void LoadKeybindings();

	public:
		//Public member functions
		void HandleInput(KeyboardInput input);
		void ReceiveMessage(Message message) override;
	};

}