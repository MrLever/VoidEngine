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
#include "InputAxis.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace EngineCoreTests {

	using namespace EngineCore;
	TEST_CLASS(InputDefinitionTests) {
		TEST_METHOD(GenericInputGetButtonTest) {
			auto time = EngineUtils::GetGameTime();
			
			auto button = KeyboardButton::A;

			KeyboardInput test(
				button, 
				ButtonState::PRESSED, 
				InputModifier::NONE,
				time
			);
			
			Assert::IsTrue(KeyboardButton::A == test.GetButton());
		}
		TEST_METHOD(KeyboardInputGetButtonTest) {
			auto button = KeyboardButton::A;
			KeyboardInput keyboardInput(button, ButtonState::PRESSED);
			
			Assert::IsTrue(button == keyboardInput.GetButton());
		}

		TEST_METHOD(MouseInputGetButtonTest) {
			auto button = MouseButton::Left;
			MouseInput mouseInput(button, ButtonState::PRESSED);

			Assert::IsTrue(button == mouseInput.GetButton());
		}

		TEST_METHOD(GamepadInputGetGamepadInputTest) {
			auto button = GamepadButton::A;
			GamepadInput gamepadInput(button, ButtonState::PRESSED, 0);

			Assert::IsTrue(button == gamepadInput.GetButton());
		}
	};

}