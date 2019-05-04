#include <memory>
#include <iostream>

#include "stdafx.h"
#include "CppUnitTest.h"


#include "..\Source\EventTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace ProjectCoatiTestSuite {

	using namespace EngineCore;
	
	TEST_CLASS(EventTableTests) {
	public:



		TEST_METHOD(BindEventTest) {
			EventTable dummyTable;
			Message dummyMessage("Test", MessageType::GenericEvent);
			
			bool dummyFlag = false;
			dummyTable.BindEvent(
				dummyMessage, 
				[&]() -> void {
					dummyFlag = true;
				}
			);

			//Run the lambda expression definded above to flip the flag
			dummyTable[dummyMessage]();

			Assert::IsTrue(dummyFlag);
		}

		TEST_METHOD(UnbindEventTest) {
			EventTable dummyTable;
			Message dummyMessage("Test", MessageType::GenericEvent);

			
			dummyTable.BindEvent(
				dummyMessage,
				[]() -> void {
					std::cout << "Testing\n";
				}
			);

			dummyTable.UnbindEvent(dummyMessage);

			Assert::IsTrue(dummyTable[dummyMessage] == nullptr);
		}

		TEST_METHOD(IndexOperatorTest) {
			EventTable dummyTable;
			Message dummyMessage("Test", MessageType::GenericEvent);

			dummyTable.BindEvent(
				dummyMessage,
				[]() -> void {
				
				}
			);

			Assert::IsTrue(dummyTable[dummyMessage] != nullptr);
		}

	};
}