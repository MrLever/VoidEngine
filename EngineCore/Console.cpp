//STD Headers
#include <iostream>
#include <utility>

//Library Headers

//Coati Headers
#include "Console.h"
#include "MessageBus.h"
#include "TimeUtils.h"

namespace core {

	//CTORS
	Console::Console(std::shared_ptr<MessageBus> Bus) : MessageBusNode(std::move(Bus)){
		OutputActive = true;
		RegisterReciever();
		RegisterEvents();
	}

	//Private Member Functions

	void Console::Log(const std::string message, LogLevel level = LogLevel::DEBUG) {
		std::string prefix = std::to_string(utils::GetGameTime());
		switch (level) {
			case LogLevel::INFO:
				prefix += " INFO: ";
				break;
			case LogLevel::DEBUG:
				prefix += " DEBUG: ";
				break;
			case LogLevel::WARNING:
				prefix += " WARNING: ";
				break;
			default:
				prefix += " ERROR: ";
		}

		Message logMessage(prefix + message, MessageType::Log);

		GameMessageBus->PublishMessage(logMessage);

	}

	void Console::ToggleOutputActive(){
		OutputActive = !OutputActive;
	}

	void Console::RegisterReciever() {
		GameMessageBus->AddReceiver(
			this,
			MessageType::ACK
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
			std::cout << message.GetEvent() << "\n";
		}
		
		MessageBusNode::ReceiveMessage(message);
	}

}