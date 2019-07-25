#include <memory>
#include <iostream>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "MessageBus.h"
#include "MessageBusNode.h"
#include "Message.h"
#include "TestingUtilities.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace GameplayFrameworkTests {
	using namespace EngineCore;
	using namespace EngineUtils;
	using namespace EngineTestSuiteUtils;

	TEST_CLASS(MessageBusTests) {
	public:

		TEST_METHOD(RecieveMessageTest) {
			std::shared_ptr<MessageBus> testBus = std::make_shared<MessageBus>();
			DummyReceiver testReceiver(testBus);
			Message testMessage("Test", MessageType::DebugACK);

			testBus->PublishMessage(testMessage);
			testBus->DispatchMessages();

			Assert::IsTrue(testReceiver.MessageReceived);
		}

		TEST_METHOD(IgnoreMessageTest) {
			std::shared_ptr<MessageBus> testBus = std::make_shared<MessageBus>();
			DummyReceiver testReceiver(testBus);
			Message testMessage("Test", MessageType::DebugNACK);

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