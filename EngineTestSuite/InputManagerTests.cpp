#include <memory>
#include <iostream>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "MessageBus.h"
#include "InputManager.h"
#include "InputInterfaceManager.h"
#include "TestingUtilities.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace EngineCoreTests {

	using namespace EngineCore;
	TEST_CLASS(InputManagerTests) {
	public:
		TEST_METHOD(TriggerKeybindingTest) {

			//Keybindings are meant to trigger events.

			std::shared_ptr<InputInterfaceManager> DummyInterface;
			InputManager dummyManager(DummyInterface);

			KeyboardInput dummyInput(KeyboardButton::ESC, ButtonState::Pressed);
			Message dummyMessage("End Game", MessageType::Termination);
			
			//dummyManager.AddKeyBinding(dummyInput, dummyMessage);

			Assert::Fail();
		}

	};
}