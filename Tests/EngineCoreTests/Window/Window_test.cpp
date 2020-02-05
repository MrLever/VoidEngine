//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "core/Window.h"

namespace EngineCoreTests {		

	using namespace core;

	TEST(WindowManagerTests, WindowCreationTest) {
		WindowData d = { "Test", 600, 800 };
		Window test(nullptr, d);

		ASSERT_TRUE(true);
	}

}