#include <memory>
#include <iostream>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Source\EngineUtilities.h"
#include "..\Source\GenericInput.h"
#include "..\Source\KeyboardInput.h"
#include "..\Source\MouseInput.h"
#include "..\Source\GamepadInput.h"
#include "..\Source\InputAxis.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace ProjectCoatiTestSuite {

	using namespace EngineCore;
	TEST_CLASS(InputDefinitionTests) {
		TEST_METHOD(GenericInputGetButtonTest) {
			auto time = EngineUtilities::GetGameTime();
			

			GenericInput test(
				static_cast<unsigned>(KeyboardButton::A), 
				ButtonState::Pressed, time
			);
			
			if (KeyboardButton::A == static_cast<KeyboardButton>(test.GetButton())) {
				Assert::IsTrue(true);
			}
			else {
				Assert::Fail();
			}
		}

		TEST_METHOD(GenericInputGetButtonStateTest) {
			auto time = EngineUtilities::GetGameTime();


			GenericInput test(
				static_cast<unsigned>(KeyboardButton::A),
				ButtonState::Pressed, time
			);

			if (ButtonState::Pressed == static_cast<ButtonState>(test.GetButtonState())) {
				Assert::IsTrue(true);
			}
			else {
				Assert::Fail();
			}
		}

		TEST_METHOD(GenericInputGetTimestampTest) {
			auto time = EngineUtilities::GetGameTime();


			GenericInput test(
				static_cast<unsigned>(KeyboardButton::A),
				ButtonState::Pressed, time
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

			if (keyboardHandle->GetKeyboardButton() == button) {
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
			MouseInput* keyboardHandle = dynamic_cast<MouseInput*>(genericHandle);

			if (keyboardHandle->GetMouseButton() == button) {
				Assert::IsTrue(true);
			}
			else {
				Assert::Fail();
			}
		}

		TEST_METHOD(GamepadInputGetGamepadInputTest) {
			
			//Gamepad input is not properly defined yet.
			//Assert fail until defined.
			Assert::Fail();
		}
	};

}