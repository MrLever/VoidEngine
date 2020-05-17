//STD Headers
#include <memory>
#include <iostream>

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "utils/EngineUtilities.h"

#include "core/input/definitions/Input.h"
#include "core/input/definitions/GamepadInput.h"
#include "core/input/definitions/KeyboardInput.h"
#include "core/input/definitions/MouseInput.h"

namespace core_tests {

	using namespace core;

	TEST(InputDefinitionTests, GenericInputGetButtonTest) {
		auto time = utils::GetGameTime();
			
		auto button = KeyboardButton::A;

		KeyboardInput test(
			button, 
			ButtonState::PRESSED, 
			InputModifier::NONE,
			time
		);
			
		ASSERT_TRUE(KeyboardButton::A == test.GetButton());
	}

	TEST(InputDefinitionTests, GenericInputEqualityTest) {
		KeyboardInput input1(KeyboardButton::A, ButtonState::PRESSED, 0, 0);
		KeyboardInput input2(KeyboardButton::A, ButtonState::PRESSED, 0, 100);

		ASSERT_TRUE(input1 == input2);
		ASSERT_TRUE(input1.Hash() == input2.Hash());
	}

	TEST(InputDefinitionTests, KeyboardInputGetButtonTest) {
		auto button = KeyboardButton::A;
		KeyboardInput keyboardInput(button, ButtonState::PRESSED);
			
		ASSERT_TRUE(button == keyboardInput.GetButton());
	}

	TEST(InputDefinitionTests, MouseInputGetButtonTest) {
		auto button = MouseButton::LEFT;
		MouseInput mouseInput(button, ButtonState::PRESSED);

		ASSERT_TRUE(button == mouseInput.GetButton());
	}

	TEST(InputDefinitionTests, GamepadInputGetGamepadInputTest) {
		auto button = GamepadButton::A;
		GamepadInput gamepadInput(button, ButtonState::PRESSED, (utils::GameTime)0);

		ASSERT_TRUE(button == gamepadInput.GetButton());
	}

}