#include <memory>
#include <iostream>

#include "stdafx.h"
#include "CppUnitTest.h"


#include "..\Source\InputAxis.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace ProjectCoatiTestSuite {

	using namespace EngineCore;

	TEST_CLASS(InputAxisTests) {
	public:
		
		TEST_METHOD(BindAxisTest) {
			InputAxis dummyAxis;
			dummyAxis.AddBinding(KeyType::W, 1.0);

			//If binding was successfull (no crash), then success.
			Assert::IsTrue(true);
		}

		TEST_METHOD(UpdateAxisTest) {
			InputAxis dummyAxis;
			dummyAxis.AddBinding(KeyType::W, 1.0);
			dummyAxis.AddBinding(KeyType::S, -1.0);

			double axisValue;

			axisValue = dummyAxis.Poll();
			if (axisValue != 0) {
				Assert::Fail();
			}

			KeyboardInput dummyWPress(KeyType::W, KeyState::Pressed);
			KeyboardInput dummyWHold(KeyType::W, KeyState::Held);
			KeyboardInput dummyWRelease(KeyType::W, KeyState::Released);

			KeyboardInput dummySPress(KeyType::S, KeyState::Pressed);
			KeyboardInput dummySHold(KeyType::S, KeyState::Held);
			KeyboardInput dummySRelease(KeyType::S, KeyState::Released);

			//Pressing should update axis with associated scale value
			dummyAxis.UpdateAxis(dummyWPress);
			axisValue = dummyAxis.Poll();
			if (axisValue != 1.0) {
				Assert::Fail();
			}

			//Holding a key should have no effect
			dummyAxis.UpdateAxis(dummyWHold);
			axisValue = dummyAxis.Poll();
			if (axisValue != 1.0) {
				Assert::Fail();
			}

			//Releasing a key should reset the axis
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

			//Releasing a binded key while holding two or more bindings
			//should revert to the last held binding
			dummyAxis.UpdateAxis(dummyWPress);
			dummyAxis.UpdateAxis(dummySPress);
			dummyAxis.UpdateAxis(dummyWRelease);
			axisValue = dummyAxis.Poll();
			if (axisValue != -1.0) {
				Assert::Fail();
			}

		}
		TEST_METHOD(ResetAxis) {
			InputAxis dummyAxis;
			dummyAxis.AddBinding(KeyType::W, 1.0);
			
			KeyboardInput dummyIn(KeyType::W, KeyState::Pressed);

			dummyAxis.UpdateAxis(dummyIn);
			dummyAxis.Reset();
			double value = dummyAxis.Poll();

			if (value != 0) {
				Assert::Fail();
			}
		}
	};
}