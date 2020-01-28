//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "EngineCore/Factory.h"
#include "EngineCore/Entity.h"
#include "EngineCore/DefaultPlayerEntity.h"

using namespace utils;

namespace utils_tests {

	class TestEntity : public core::DefaultPlayerEntity {
		TYPE_INFO_DECL(TestEntity)
	};

	TYPE_INFO_IMPL(TestEntity)
	
	ENABLE_FACTORY(TestEntity, core::Entity)
	TEST(FactoryTests, ConstructionTest) {
		core::Entity* testEntity = FactoryBase<core::Entity>::Create("TestEntity");
		ASSERT_NE(nullptr, testEntity);
	}
}