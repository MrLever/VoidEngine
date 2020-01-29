//STD Headers
#include <memory>
#include <iostream>

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "EngineCore/EngineUtilities.h"

using namespace utils;

namespace EngineUtilitiesTests{

	TEST(GenericEngineUtilitiesTests, FNV1aEqualityTest) {
		auto first = FNV1aHash("ThisIsATest");
		auto second = FNV1aHash("ThisIsATest");

		ASSERT_EQ(first, second);
	}

	TEST(GenericEngineUtilitiesTests, FNV1aInequalityTest) {
		auto first = FNV1aHash("ThisIsATest");
		auto second = FNV1aHash("ThisTooIsATest");
		auto third = FNV1aHash("YesYesThisTooIsATest");
		ASSERT_NE(first, second);
		ASSERT_NE(first, third);
		ASSERT_NE(second, third);
	}

}