//STD Headers
#include <iostream>

//Library Headers

//Coati Headers
#include "Console.h"
#include "MessageBus.h"

namespace EngineCore {

	//CTORS
	Console::Console(std::shared_ptr<MessageBus> Bus) : MessageBusNode(Bus){
		OutputActive = true;
		this->RegisterReciever();
		this->RegisterEvents();
	}


	Console::~Console(){

	}

	//Private Member Functions

	void Console::ToggleOutputActive(){
		OutputActive = !OutputActive;
	}

	void Console::RegisterReciever() {
		GameMessageBus->AddReceiver(
			this,
			MessageType::DebugAck
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
	void Console::ReceiveMessage(Message message) {
		if (OutputActive) {
			std::cout << "CONSOLE: " << message.GetEvent() << "\n";
		}
		
		if (Events[message]) {
			Events[message]();
		}
	}

}