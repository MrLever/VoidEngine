//STD Headers
#include <memory>
#include <iostream>

//Library Headers
#include "stdafx.h"
#include "CppUnitTest.h"

//Void Engine Headers
#include "EngineUtilities.h"
#include "GenericInput.h"
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
			

			GenericInput test(
				static_cast<unsigned>(KeyboardButton::A), 
				ButtonState::Pressed, 
				time
			);
			
			if (KeyboardButton::A == static_cast<KeyboardButton>(test.GetButton<KeyboardButton>())) {
				Assert::IsTrue(true);
			}
			else {
				Assert::Fail();
			}
		}

		TEST_METHOD(GenericInputGetButtonStateTest) {
			auto time = EngineUtils::GetGameTime();


			GenericInput test(
				static_cast<unsigned>(KeyboardButton::A),
				ButtonState::Pressed, 
				time
			);

			if (ButtonState::Pressed == static_cast<ButtonState>(test.GetButtonState())) {
				Assert::IsTrue(true);
			}
			else {
				Assert::Fail();
			}
		}

		TEST_METHOD(GenericInputGetTimestampTest) {
			auto time = EngineUtils::GetGameTime();


			GenericInput test(
				static_cast<unsigned>(KeyboardButton::A),
				ButtonState::Pressed, 
				time
			);

			if (time == test.GetTimeStamp()) {
				Assert::IsTrue(true);
			}
			else {
				Assert::Fail();
			}
		}

		TEST_METHOD(KeyboardInputGetKeyboardInputTest) {
			auto button = KeyboardButton::A;
			KeyboardInput keyboardInput(button, ButtonState::Pressed, 0);
			
			//Shove it into a generic handle
			GenericInput* genericHandle = &keyboardInput;

			//Bring it back to the correct handle
			KeyboardInput* keyboardHandle = dynamic_cast<KeyboardInput*>(genericHandle);

			if (keyboardHandle->GetButton<KeyboardButton>() == button) {
				Assert::IsTrue(true);
			}
			else {
				Assert::Fail();
			}
		}

		TEST_METHOD(MouseInputGetMouseInputTest) {
			auto button = MouseButton::Left;
			MouseInput keyboardInput(button, ButtonState::Pressed, 0);

			//Shove it into a generic handle
			GenericInput* genericHandle = &keyboardInput;

			//Bring it back to the correct handle
			MouseInput* mouseHandle = dynamic_cast<MouseInput*>(genericHandle);

			if (mouseHandle->GetButton<MouseButton>() == button) {
				Assert::IsTrue(true);
			}
			else {
				Assert::Fail();
			}
		}

		TEST_METHOD(GamepadInputGetGamepadInputTest) {
			auto button = GamepadButton::A;
			GamepadInput keyboardInput(button, ButtonState::Pressed, 0);

			//Shove it into a generic handle
			GenericInput* genericHandle = &keyboardInput;

			//Bring it back to the correct handle
			GamepadInput* gamepadHandle = dynamic_cast<GamepadInput*>(genericHandle);

			if (gamepadHandle->GetButton<GamepadButton>() == button) {
				Assert::IsTrue(true);
			}
			else {
				Assert::Fail();
			}
		}
	};

}