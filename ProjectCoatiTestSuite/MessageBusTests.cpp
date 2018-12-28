#include <memory>

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
		std::shared_ptr<MessageBus> bus;
		DummyReceiver(std::shared_ptr<MessageBus> bus) : MessageBusNode(bus) {
			this->bus = bus;
			MessageReceived = false;
			this->RegisterReciever();
		}
		~DummyReceiver() {
		}

		void ReceiveMessage(Message message) override{
			MessageReceived = true;
		}
	};
	class FilteredDummyReceiver : MessageBusNode {
	public:
		bool MessageReceived;
		std::shared_ptr<MessageBus> bus;
		FilteredDummyReceiver(std::shared_ptr<MessageBus> bus) : MessageBusNode(bus){
			this->bus = bus;
			MessageReceived = false;
			this->RegisterReciever();
		}
		~FilteredDummyReceiver() {
		}
		virtual void RegisterReciever() override {
			bus->AddReciever(this, Input);
		}
		void ReceiveMessage(Message message) override {
			MessageReceived = true;
		}
	};

	TEST_CLASS(MessageBusTests) {
	public:

		TEST_METHOD(RecieveMessageTest) {
			std::shared_ptr<MessageBus> testBus = std::make_shared<MessageBus>();
			DummyReceiver testReceiver(testBus);
			Message testMessage("Test", Initialization);

			testBus->PublishMessage(testMessage);
			testBus->DispatchMessages();

			Assert::IsTrue(testReceiver.MessageReceived);
		}

		TEST_METHOD(IgnoreMessageTest) {
			std::shared_ptr<MessageBus> testBus = std::make_shared<MessageBus>();
			FilteredDummyReceiver testReceiver(testBus);
			Message testMessage("Test", Termination);

			testBus->PublishMessage(testMessage);
			testBus->DispatchMessages();

			Assert::IsFalse(testReceiver.MessageReceived);
		}
	};
}