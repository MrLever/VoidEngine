//STD Headers
#include <memory>
#include <iostream>

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "EngineUtilities.h"
#include "Input.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "GamepadInput.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace EngineCoreTests {

	using namespace core;
	TEST_CLASS(InputDefinitionTests) {
		TEST_METHOD(GenericInputGetButtonTest) {
			auto time = utils::GetGameTime();
			
			auto button = KeyboardButton::A;

			KeyboardInput test(
				button, 
				ButtonState::PRESSED, 
				InputModifier::NONE,
				time
			);
			
			Assert::IsTrue(KeyboardButton::A == test.GetButton());
		}

		TEST_METHOD(GenericInputEqualityTest) {
			KeyboardInput input1(KeyboardButton::A, ButtonState::PRESSED, 0, 0);
			KeyboardInput input2(KeyboardButton::A, ButtonState::PRESSED, 0, 100);

			Assert::IsTrue(input1 == input2);
			Assert::IsTrue(input1.Hash() == input2.Hash());
		}

		TEST_METHOD(KeyboardInputGetButtonTest) {
			auto button = KeyboardButton::A;
			KeyboardInput keyboardInput(button, ButtonState::PRESSED);
			
			Assert::IsTrue(button == keyboardInput.GetButton());
		}

		TEST_METHOD(MouseInputGetButtonTest) {
			auto button = MouseButton::LEFT;
			MouseInput mouseInput(button, ButtonState::PRESSED);

			Assert::IsTrue(button == mouseInput.GetButton());
		}

		TEST_METHOD(GamepadInputGetGamepadInputTest) {
			auto button = GamepadButton::A;
			GamepadInput gamepadInput(button, ButtonState::PRESSED, (utils::GameTime)0);

			Assert::IsTrue(button == gamepadInput.GetButton());
		}
	};

}