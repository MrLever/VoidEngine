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

	TEST_CLASS(FactoryTests) {
	public:
		TEST_METHOD(FactoryProductionTest) {
			utils::Factory<core::DefaultPlayerEntity, core::Entity> DefaultPlayerEntityFactory;
			core::Entity* testEntity = FactoryBase<core::Entity>::Create("DefaultPlayerEntity");
			Assert::IsNotNull(testEntity);
		}
	};
}