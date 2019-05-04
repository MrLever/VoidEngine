#pragma once
namespace ProjectCoatiTestSuite
{
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

		void ReceiveMessage(Message message) override {
			MessageReceived = true;
			if (Events[message]) {
				Events[message]();
			}

		}

		void FireEvent() {
			std::cout << "Event Fired";
			EventFired = true;
		}
	};
}