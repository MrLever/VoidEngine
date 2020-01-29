//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "EngineCore/Entity.h"
#include "EngineCore/GraphicsComponent.h"
#include "EngineCore/InputComponent.h"

using namespace core;

namespace EngineCoreTests {

	class DummyEntity : public Entity {
		void BeginPlay() override {}
		void Terminate() override {}
	};

	TEST(TestEntites, GetComponentTest) {
		DummyEntity dummy;
		dummy.AddComponent(new GraphicsComponent());

		auto model = dummy.GetComponent<GraphicsComponent>();
		auto brokenComponent = dummy.GetComponent<InputComponent>();

		ASSERT_NE(nullptr, model);
		ASSERT_EQ(nullptr, brokenComponent);
	}

}