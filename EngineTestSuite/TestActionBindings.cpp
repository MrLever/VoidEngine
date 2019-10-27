//STD Headers

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "PlayerEntity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace core;

namespace EngineCoreTests {
	class TestPlayer : public PlayerEntity {
	public:
		TestPlayer(const std::string& name) : PlayerEntity(name) {
			MovedForward = Jumped = false;
			
		}

		virtual void SetupInputComponent(InputComponent* component) {
			Components.push_back(component);
			component->BindAction(
				"Jump", 
				ActionType::PRESSED,
				[this](float deltaTime) {Jump(deltaTime); }
			);

			component->BindAxis(
				"MoveForward",
				[this](float value, float deltaTime) {MoveForward(value, deltaTime); }
			);
		}

		void MoveForward(float scale, float deltaTime) {
			MovedForward = true;
		}

		void Jump(float deltaTime) {
			Jumped = true;
		}

		bool MovedForward;
		bool Jumped;
	};


	TEST_CLASS(ActionBindingTests) {
		TEST_METHOD(AddBindingTest) {
			TestPlayer test("test");
			test.SetupInputComponent(new InputComponent(&test));


			test.Input(InputAction("Unbound input"), 0);
			Assert::IsFalse(test.MovedForward);
			Assert::IsFalse(test.Jumped);

			test.Input(InputAxisAction("MoveForward", 1), 0);
			Assert::IsTrue(test.MovedForward);

			test.Input(InputAction("Jump"), 0);
			Assert::IsTrue(test.Jumped);
		}
	};

}