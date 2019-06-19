#include <memory>
#include <iostream>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "KeyBindings.h"
#include "Message.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace ProjectCoatiTestSuite {

	using namespace EngineCore;

	TEST_CLASS(KeyBindingsTests) {
	public:
		TEST_METHOD(LoadBindingsTest) {
			Keybindings dummyBindings;

			Assert::IsTrue(dummyBindings.Load());
		}
		TEST_METHOD(SaveBindingsTest) {
			Keybindings dummyBindings("Settings/debugInput.ini");
			
			KeyboardInput dummyInput(KeyboardButton::NUM_9, ButtonState::Pressed);
			Message dummyMessage("test", MessageType::GenericEvent);

			//dummyBindings.AddBinding(dummyInput, dummyMessage);
			dummyBindings.Save();
			dummyBindings.Load();

			//Remove the binding to preserve the state of the test input file.
			//This also ensures the bindings are reloaded properly.
			Assert::IsTrue(dummyBindings.RemoveBinding(dummyInput));
		}
		TEST_METHOD(AddBindingTest) {
			//Initialization
			Keybindings dummyBindings;
			KeyboardInput dummyInput(KeyboardButton::NUM_9, ButtonState::Pressed);
			Message dummyMessage("test", MessageType::GenericEvent);

			//Test
			//Assert::IsTrue(dummyBindings.AddBinding(dummyInput, dummyMessage));
		}
		TEST_METHOD(RemoveBindingTest) {
			//Initialization
			Keybindings dummyBindings;
			KeyboardInput dummyInput(KeyboardButton::NUM_9, ButtonState::Pressed);
			Message dummyMessage("test", MessageType::GenericEvent);

			//dummyBindings.AddBinding(dummyInput, dummyMessage);


			//Test
			Assert::IsTrue(dummyBindings.RemoveBinding(dummyInput));
		}
		TEST_METHOD(ReassignBindingTest) {
			//Initialization
			Keybindings dummyBindings;
			KeyboardInput dummyInput(KeyboardButton::NUM_9, ButtonState::Pressed);
			Message dummyMessage("test", MessageType::GenericEvent);

			//dummyBindings.AddBinding(dummyInput, dummyMessage);
			//dummyBindings.ReassignBinding

			//Test
			Assert::IsTrue(dummyBindings.RemoveBinding(dummyInput));
		}
	};
}