//STD Headers

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "Window.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineCoreTests {		

	using namespace core;

	TEST_CLASS(WindowManagerTests) {
	public:
		
		TEST_METHOD(WindowCreationTest) {
			WindowData d = { "Test", 600, 800 };
			Window test(nullptr, d);

			Assert::IsTrue(true);
		}
	};
}