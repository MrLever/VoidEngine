//STD Headers
#include <memory>
#include <iostream>

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "MessageBus.h"
#include "MessageBusNode.h"
#include "Message.h"
#include "TestingUtilities.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace GameplayFrameworkTests {
	using namespace core;
	using namespace utils;
	using namespace EngineTestSuiteUtils;

	TEST_CLASS(MessageBusTests) {
	public:

		TEST_METHOD(RecieveMessageTest) {
			std::shared_ptr<MessageBus> testBus = std::make_shared<MessageBus>();
			DummyReceiver testReceiver(testBus);
			Message testMessage("Test", MessageType::ACK);

			testBus->PublishMessage(testMessage);
			testBus->DispatchMessages();

			Assert::IsTrue(testReceiver.MessageReceived);
		}

		TEST_METHOD(IgnoreMessageTest) {
			std::shared_ptr<MessageBus> testBus = std::make_shared<MessageBus>();
			DummyReceiver testReceiver(testBus);
			Message testMessage("Test", MessageType::NACK);

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