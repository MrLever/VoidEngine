//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "core/platform/Platform.h"

namespace EngineCoreTests {		

	using namespace core;

	TEST(WindowManagerTests, WindowCreationTest) {
		WindowData data = { "test", 1, 1 };
		auto window = platform::MakeWindow(nullptr, data);

		ASSERT_NE(nullptr, window);
	}

}