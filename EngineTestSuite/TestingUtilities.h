#pragma once
//STD Headers
#include <memory>

//Library Headers

//Void Engine Headers
#include "MessageBus.h"
#include "MessageBusNode.h"
#include "Console.h"

namespace EngineTestSuiteUtils
{

	using namespace core;

	class DummyReceiver : MessageBusNode {
	public:
		bool MessageReceived;
		bool EventFired;

		DummyReceiver(MessageBus* bus) : MessageBusNode(bus) {
			MessageReceived = false;
			EventFired = false;
			this->RegisterReciever();
			this->RegisterEvents();
		}
		~DummyReceiver() {

		}

		void RegisterEvents() override {
			//Events.BindEvent(Message("FireTestEvent", MessageType::Input), &FireEvent);
			auto eventLambda = [=]() -> void {
				this->FireEvent();
			};

			Events.BindEvent(Message("End Game", MessageType::Termination), eventLambda);
			Events.BindEvent(Message("FireTestEvent", MessageType::Input), eventLambda);
		}

		void RegisterReciever() override {
			Bus->AddReceiver(this, MessageType::Input);
			Bus->AddReceiver(this, MessageType::Termination);
		}

		void ReceiveMessage(const Message &message) override {
			MessageReceived = true;
			if (Events[message]) {
				Events[message]();
			}

		}

		void DebugPublishEvent(std::string s) {
			this->PublishMessage(Message(s, MessageType::ACK));
		}

		void FireEvent() {
			EventFired = true;
		}
	};

	class DebugConsole : public Console {
	public:

		bool ToggleSignalReceived;

		DebugConsole(MessageBus* bus) : Console(bus){
			ToggleSignalReceived = false;
		}

		void ReceiveMessage(const Message &message) override {
			if (message.GetEvent() == "Toggle Console Output") {
				ToggleSignalReceived = true;
			}
		}
	};
}