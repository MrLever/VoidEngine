#pragma once

#include "MessageBus.h"
#include "MessageBusNode.h"
#include "Console.h"

namespace ProjectCoatiTestSuite
{

	using namespace EngineCore;

	class DummyReceiver : MessageBusNode {
	public:
		bool MessageReceived;
		bool EventFired;
		std::shared_ptr<MessageBus> bus;

		DummyReceiver(std::shared_ptr<MessageBus> bus) : MessageBusNode(bus) {
			this->bus = bus;
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
			bus->AddReceiver(this, MessageType::Input);
			bus->AddReceiver(this, MessageType::Termination);
		}

		void ReceiveMessage(const Message &message) override {
			MessageReceived = true;
			if (Events[message]) {
				Events[message]();
			}

		}

		void DebugPublishEvent(std::string s) {
			this->PublishMessage(Message(s, MessageType::DebugACK));
		}

		void FireEvent() {
			EventFired = true;
		}
	};

	class DebugConsole : public Console {
	public:

		bool ToggleSignalReceived;

		DebugConsole(std::shared_ptr<MessageBus> bus) : Console(bus){
			ToggleSignalReceived = false;
		}

		void ReceiveMessage(const Message &message) override {
			if (message.GetEvent() == "Toggle Console Output") {
				ToggleSignalReceived = true;
			}
		}
	};
}