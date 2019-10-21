//STD Headers
#include <memory>

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "TestingUtilities.h"
#include "Console.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace core;

namespace EngineUtilitiesTests {
	using namespace core;
	using namespace EngineTestSuiteUtils;

	TEST_CLASS(ConsoleTests) {
	public:
		TEST_METHOD(ToggleOutputTest) {
			std::shared_ptr<MessageBus> testBus = std::make_shared<MessageBus>();
			DummyReceiver dummy(testBus.get());
			DebugConsole console(testBus.get());
			dummy.DebugPublishEvent("Toggle Console Output");
			
			testBus->DispatchMessages();

			Assert::IsTrue(console.ToggleSignalReceived);
		}
	};
}