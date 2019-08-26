//STD Headers
#include <memory>
#include <iostream>

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
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
			auto engineInterface = EngineTestSuiteUtils::CreateEngineInterface();
			std::shared_ptr<InputInterfaceManager> DummyInterface;
			InputManager dummyManager(DummyInterface, engineInterface, "Settings/Testing/InputConfig.lua");

			KeyboardInput dummyInput(KeyboardButton::ESC, ButtonState::Pressed);
			Message dummyMessage("End Game", MessageType::Termination);
			
			//dummyManager.AddKeyBinding(dummyInput, dummyMessage);

			Assert::Fail();
		}

	};
}