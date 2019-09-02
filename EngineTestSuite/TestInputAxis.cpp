//STD Headers
#include <memory>
#include <iostream>

//Library headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "InputAxis.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace EngineCoreTests {

	using namespace EngineCore;

	TEST_CLASS(InputAxisTests) {
	public:
		
		TEST_METHOD(BindAxisTest) {
			InputAxis dummyAxis("test");
			dummyAxis.AddBinding(KeyboardButton::W, 1.0);

			//If binding was successfull (no crash), then success.
			Assert::IsTrue(true);
		}

		TEST_METHOD(ResetAxis) {
			InputAxis dummyAxis("test");
			dummyAxis.AddBinding(KeyboardButton::W, 1.0);

			KeyboardInput dummyIn(
				KeyboardButton::W, ButtonState::PRESSED
			);

			dummyAxis.UpdateAxis(dummyIn);
			dummyAxis.Reset();
			double value = dummyAxis.Poll();

			if (value != 0) {
				Assert::Fail();
			}
		}
		TEST_METHOD(UpdateAxisTest) {
			InputAxis dummyAxis("test");
			dummyAxis.AddBinding(KeyboardButton::W, 1.0);
			dummyAxis.AddBinding(KeyboardButton::S, -1.0);

			double axisValue;

			axisValue = dummyAxis.Poll();
			if (axisValue != 0) {
				Assert::Fail();
			}

			KeyboardInput dummyWPress(KeyboardButton::W, ButtonState::PRESSED);
			KeyboardInput dummyWHold(KeyboardButton::W, ButtonState::HELD);
			KeyboardInput dummyWRelease(KeyboardButton::W, ButtonState::RELEASED);

			KeyboardInput dummySPress(KeyboardButton::S, ButtonState::PRESSED);
			KeyboardInput dummySHold(KeyboardButton::S, ButtonState::HELD);
			KeyboardInput dummySRelease(KeyboardButton::S, ButtonState::RELEASED);

			//Pressing should update axis with associated scale value
			dummyAxis.UpdateAxis(dummyWPress);
			axisValue = dummyAxis.Poll();
			if (axisValue != 1.0) {
				Assert::Fail();
			}
			dummyAxis.Reset();

			//Holding a key should have no effect
			dummyAxis.UpdateAxis(dummyWHold);
			axisValue = dummyAxis.Poll();
			if (axisValue != 0.0) {
				Assert::Fail();
			}
			dummyAxis.Reset();

			//Releasing a key should reset the axis if there are no other held keys
			dummyAxis.UpdateAxis(dummyWPress);
			dummyAxis.UpdateAxis(dummyWRelease);
			axisValue = dummyAxis.Poll();
			if (axisValue != 0.0) {
				Assert::Fail();
			}

			//Pressing a conflicting axis value should overwrite axis
			dummyAxis.UpdateAxis(dummyWPress);
			dummyAxis.UpdateAxis(dummySPress);
			axisValue = dummyAxis.Poll();
			if (axisValue != -1.0) {
				Assert::Fail();
			}
			dummyAxis.Reset();

			//Releasing a binded key while holding two or more bindings
			//should revert to the last held binding
			dummyAxis.UpdateAxis(dummyWPress);
			dummyAxis.UpdateAxis(dummySPress);
			dummyAxis.UpdateAxis(dummyWRelease);
			axisValue = dummyAxis.Poll();
			if (axisValue != -1.0) {
				Assert::Fail();
			}

			dummyAxis.UpdateAxis(dummyWPress);
			dummyAxis.UpdateAxis(dummySPress);
			dummyAxis.UpdateAxis(dummySRelease);
			axisValue = dummyAxis.Poll();
			if (axisValue != 1.0) {
				Assert::Fail();
			}

		}
		
	};
}