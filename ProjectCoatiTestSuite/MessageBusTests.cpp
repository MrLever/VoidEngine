#include <memory>
#include <iostream>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Source\MessageBus.h"
#include "..\Source\MessageBusNode.h"
#include "..\Source\Message.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace ProjectCoatiTestSuite
{
	class DummyReceiver : MessageBusNode {
	public:
		bool MessageReceived;
		bool EventFired;
		std::shared_ptr<MessageBus> bus;
		
		DummyReceiver(std::shared_ptr<MessageBus> bus) : MessageBusNode(bus){
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

			Events.BindEvent(Message("FireTestEvent", MessageType::Input), eventLambda);
		}

		void RegisterReciever() override {
			bus->AddReceiver(this, MessageType::Input);
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

	TEST_CLASS(MessageBusTests) {
	public:

		TEST_METHOD(RecieveMessageTest) {
			std::shared_ptr<MessageBus> testBus = std::make_shared<MessageBus>();
			DummyReceiver testReceiver(testBus);
			Message testMessage("Test", MessageType::Input);

			testBus->PublishMessage(testMessage);
			testBus->DispatchMessages();

			Assert::IsTrue(testReceiver.MessageReceived);
		}

		TEST_METHOD(IgnoreMessageTest) {
			std::shared_ptr<MessageBus> testBus = std::make_shared<MessageBus>();
			DummyReceiver testReceiver(testBus);
			Message testMessage("Test", MessageType::Termination);

			testBus->PublishMessage(testMessage);
			testBus->DispatchMessages();

			Assert::IsFalse(testReceiver.MessageReceived);
		}
		
		TEST_METHOD(TriggerEventTest) {
			std::shared_ptr<MessageBus> testBus = std::make_shared<MessageBus>();
			DummyReceiver testReceiver(testBus);
			Message testMessage("FireTestEvent", MessageType::Input);

			testBus->PublishMessage(testMessage);
			testBus->DispatchMessages();


			Assert::IsTrue(testReceiver.EventFired);
		}

	};
}