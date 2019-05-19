#include <memory>
#include <iostream>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Source\MessageBus.h"
#include "..\Source\InputManager.h"
#include "..\Source\InputInterfaceManager.h"
#include "TestingUtilities.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace ProjectCoatiTestSuite {
	TEST_CLASS(InputManagerTests) {
	public:
		TEST_METHOD(TriggerKeybindingTest) {

			//Keybindings are meant to trigger events.

			std::shared_ptr<MessageBus> dummyBus = std::make_shared<MessageBus>();
			std::shared_ptr<InputInterfaceManager> DummyInterface;
			InputManager dummyManager(dummyBus, DummyInterface);
			DummyReceiver dummyReciever(dummyBus);

			KeyboardInput dummyInput(KeyType::ESC, ButtonState::Pressed);
			Message dummyMessage("End Game", MessageType::Termination);
			
			dummyManager.AddKeyBinding(dummyInput, dummyMessage);

			dummyManager.HandleInput();
			dummyBus->DispatchMessages();

			Assert::IsTrue(dummyReciever.EventFired);
		}

	};
}