//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "EngineCore/Table.h"
#include "EngineCore/Name.h"
#include "EngineCore/ColliderComponent.h"

using namespace utils;

namespace utils_tests {

	TEST(TableTests, ArrayInexOperatorTest) {
		Table<int, int, int> table;

		table[1][1] = 2;
		ASSERT_EQ(2, table[1][1]);
	}

	TEST(TableTests, FindTest) {
		Table<int, int, int> table;
		ASSERT_EQ(nullptr, table.Find(1, 1));

		table.Insert(1, 1, 164);
		ASSERT_EQ(164, table[1][1]);

		ASSERT_EQ(164, *table.Find(1, 1));
	}

	TEST(TableTests, EraseTest) {
		Table<int, int, int> table;
		table[1][1] = 100;
		ASSERT_EQ(100, *table.Find(1, 1));

		table.Erase(1, 1);

		ASSERT_EQ(nullptr, table.Find(1, 1));
	}

	TEST(TableTests, AdvancedTemplateParameterTest) {
		Table<
			utils::Name,
			utils::Name,
			std::function<bool(core::ColliderComponent*, core::ColliderComponent*)>
		> table;

		utils::Name i("i");
		utils::Name j("j");
		auto lambda = [](core::ColliderComponent*, core::ColliderComponent*) {
			return true;
		};

		table[i][j] = lambda;

		ASSERT_TRUE(table[i][j](nullptr, nullptr));
	}

}