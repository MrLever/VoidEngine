//STD Headers
#include <iostream>
#include <utility>

//Library Headers

//Coati Headers
#include "Console.h"
#include "MessageBus.h"

namespace EngineCore {

	//CTORS
	Console::Console(std::shared_ptr<MessageBus> Bus) : MessageBusNode(std::move(Bus)){
		OutputActive = true;
		this->RegisterReciever();
		this->RegisterEvents();
	}

	//Private Member Functions

	void Console::ToggleOutputActive(){
		OutputActive = !OutputActive;
	}

	void Console::RegisterReciever() {
		GameMessageBus->AddReceiver(
			this,
			MessageType::DebugACK
		);
	}

	void Console::RegisterEvents() {
		auto ToggleOutputLambda = [=]() -> void {
			this->ToggleOutputActive();
		};

		Events.BindEvent(
			Message("Toggle Console Output", MessageType::Input), 
			ToggleOutputLambda
		);
	}

	
	//Public Member Functions
	void Console::ReceiveMessage(const Message &message) {
		if (OutputActive) {
			std::cout << "CONSOLE: " << message.GetEvent() << "\n";
		}
		
		if (Events[message]) {
			Events[message]();
		}
	}

}