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
#include "InputInterface.h"


namespace EngineCore {

	//Forward Class declarations
	class MessageBus;
	class InputEvent;


	class InputManager : MessageBusNode {
	private:
		//Private class members
		Keybindings Bindings;
		std::shared_ptr<InputInterface> PlayerInterface;

	public:
		//CTORS
		InputManager(
			std::shared_ptr<MessageBus> bus, 
			std::shared_ptr<InputInterface> userInterface
		);
		~InputManager() = default;

	private:
		void RegisterReciever() override;
		void RegisterEvents() override;

		//Private member functions
		void LoadKeybindings();
		void HandleMouse();
		void HandleKeyboard();

	public:
		//Public member functions
		void AddKeyBinding(const KeyboardInput &input, const Message &message);
		void HandleInput();
		void ReceiveMessage(const Message &message) override;
	};

}