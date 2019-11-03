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
	/**
	 * ENABLE_FACTORY macro is not used here because of macro nonsense that caused segfualts in the test suite. 
	 * ENABLE_FACTORY is safe to use in production
	 */
	//ENABLE_FACTORY(TestEntity, core::Entity)

	ENABLE_TYPENAME(TestEntity)

	TEST_CLASS(FactoryTests) {
	public:
		TEST_METHOD(FactoryProductionTest) {
			utils::Factory<TestEntity, core::Entity> TestEntityFactory;

			core::Entity* testEntity = FactoryBase<core::Entity>::Create("TestEntity");
			Assert::IsNotNull(testEntity);
		}
	};
}