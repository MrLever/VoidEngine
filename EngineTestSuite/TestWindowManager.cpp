//STD Headers

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "WindowManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineCoreTests {		

	using namespace core;

	TEST_CLASS(WindowManagerTests) {
	public:
		
		TEST_METHOD(WindowCreationTest) {
			WindowManager test("Test", 600, 800);

			Assert::IsNotNull(test.GetWindow().get());
		}
	};
}