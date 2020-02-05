//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "core/gameplay_framework/entities/PlayerEntity.h"

using namespace core;

namespace EngineCoreTests {
	class TestPlayer : public PlayerEntity {
	public:
		TestPlayer() {
			MovedForward = Jumped = false;
		}

		virtual void SetupInputComponent(InputComponent* component) {
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


	TEST(ActionBindingTests, AddBindingTest) {
		TestPlayer test;
		test.Initialize();

		test.Input(InputAction("Unbound input"), 0);
		ASSERT_FALSE(test.MovedForward);
		ASSERT_FALSE(test.Jumped);

		test.Input(AxisInputAction("MoveForward", 1), 0);
		ASSERT_TRUE(test.MovedForward);

		test.Input(InputAction("Jump"), 0);
		ASSERT_TRUE(test.Jumped);
	}

}