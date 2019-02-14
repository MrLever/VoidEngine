#include <memory>
#include <iostream>

#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Source\EventTable.h"
#include "..\Source\Message.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace ProjectCoatiTestSuite {

	TEST_CLASS(EventTableTests) {
	public:
		TEST_METHOD(BindEventTest) {
			EventTable dummyTable;
			Message dummyMessage("Test", MessageType::GenericEvent);
			dummyTable.BindEvent()

			Assert::IsTrue(false);
		}

		TEST_METHOD(UnbindEventTest) {

			Assert::IsTrue(false);
		}

		TEST_METHOD(IndexOperatorTest) {

			Assert::IsTrue(false);
		}

	};
}