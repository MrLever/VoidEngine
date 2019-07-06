#include <memory>
#include <iostream>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "EngineUtilities.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace EngineTestSuite{

	TEST_CLASS(EngineUtilitiesTests) {
	public:
		TEST_METHOD(FNV1aEqualityTest) {
			auto first = EngineCore::FNV1aHash("ThisIsATest");
			auto second = EngineCore::FNV1aHash("ThisIsATest");

			Assert::AreEqual(first, second);
		}

		TEST_METHOD(FNV1aInequalityTest) {
			auto first = EngineCore::FNV1aHash("ThisIsATest");
			auto second = EngineCore::FNV1aHash("SoSoThisIsATest");

			Assert::AreNotEqual(first, second);
		}
	};
}