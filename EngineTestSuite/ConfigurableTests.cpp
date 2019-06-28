#include <memory>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "TestingUtilities.h"
#include "Configurable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineCore;

namespace ProjectCoatiTestSuite {

	class DummyConfigurable : Configurable {
		DummyConfigurable() : Configurable("testConfig.lua") {
			
		}
	};

	TEST_CLASS(ConsoleTests) {
public:
	TEST_METHOD(ToggleOutputTest) {
		
	}
	};
}