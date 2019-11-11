//STD Headers

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "Entity.h"
#include "GraphicsComponent.h"
#include "InputComponent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace core;

namespace EngineCoreTests {

	class DummyEntity : public Entity {
		void BeginPlay() override {}
		void Terminate() override {}
	};

	TEST_CLASS(TestEntites) {
	public:
		TEST_METHOD(GetComponentTest) {
			DummyEntity dummy;
			dummy.AddComponent(new GraphicsComponent());

			auto model = dummy.GetComponent<GraphicsComponent>();
			auto brokenComponent = dummy.GetComponent<InputComponent>();

			Assert::IsNotNull(model);
			Assert::IsNull(brokenComponent);
		}
	};
};