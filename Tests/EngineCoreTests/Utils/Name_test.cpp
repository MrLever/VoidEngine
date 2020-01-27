//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "EngineCore/Name.h"


using namespace utils;

namespace utils_tests {

	TEST(NameTests, Construction) {
		Name id("Test");

		ASSERT_EQ(utils::FNV1aHash("Test"), id.ID);
		ASSERT_EQ(std::string("Test"), id.StringID);
	}

	TEST(NameTests, AssignmentOperator) {
		Name id("Test");
		auto hash = id.ID;

		//String re-assignment test
		id = "Bar";
		ASSERT_EQ(std::string("Bar"), id.StringID);
		ASSERT_NE(hash, id.ID);

		//Name re-assignment test
		Name id2("Foo");
		id = id2;
		ASSERT_EQ(id2.ID, id.ID);
		ASSERT_EQ(id2.StringID, id.StringID);
	}

	TEST(NameTests, Comparison) {
		Name idA("Foo");
		Name idB("Bar");
		Name idC("Foo");

		ASSERT_TRUE(idA != idB);
		ASSERT_TRUE(idA == idC);
		ASSERT_TRUE(idA == "Foo");
		ASSERT_TRUE("Foo" == idA);
	}
};