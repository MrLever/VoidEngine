//STD Headers
#include <memory>

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "TestingUtilities.h"
#include "Console.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace EngineCore;

namespace EngineUtilitiesTests {
	using namespace EngineCore;
	using namespace EngineTestSuiteUtils;

	TEST_CLASS(ConsoleTests) {
	public:
		TEST_METHOD(ToggleOutputTest) {
			std::shared_ptr<MessageBus> testBus = std::make_shared<MessageBus>();
			DummyReceiver dummy(testBus);
			DebugConsole console(testBus);
			dummy.DebugPublishEvent("Toggle Console Output");
			
			testBus->DispatchMessages();

			Assert::IsTrue(console.ToggleSignalReceived);
		}
	};
}