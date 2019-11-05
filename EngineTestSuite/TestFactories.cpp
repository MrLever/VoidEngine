//STD Headers

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "Factory.h"
#include "Entity.h"
#include "DefaultPlayerEntity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace utils;

namespace EngineUtilitiesTests {
	class TestEntity : public core::DefaultPlayerEntity {
		
	};
	
	ENABLE_FACTORY(TestEntity, core::Entity)

	TEST_CLASS(FactoryTests) {
	public:
		TEST_METHOD(FactoryProductionTest) {
			utils::Factory<TestEntity, core::Entity> TestEntityFactory;

			core::Entity* testEntity = FactoryBase<core::Entity>::Create("TestEntity");
			Assert::IsNotNull(testEntity);
		}
	};
}