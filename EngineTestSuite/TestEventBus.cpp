//STD Headers
#include <memory>
#include <iostream>

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "EventBus.h"
#include "EventBusNode.h"
#include "Event.h"
#include "TestingUtilities.h"
#include "WindowClosedEvent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace EngineCoreTests {
	using namespace core;
	using namespace utils;
	using namespace EngineTestSuiteUtils;

	/**
		 * Helper class to connect Game to the event bus
		 */
	class TestEventBusNode : EventBusNode {
	public:
		/**
		 * Constructor
		 */
		TestEventBusNode(EventBus* bus) : EventBusNode(bus) {

		}

		virtual void ReceiveEvent(Event* event) {
			EventDispatcher dispatcher(event);
			dispatcher.Dispatch<WindowClosedEvent>(
				[this](WindowClosedEvent* windowEvent) {
					this->HandleWindowClosed(windowEvent);
				}
			);
		}

		void HandleWindowClosed(WindowClosedEvent* event) {
			Success = true;
		}

		unsigned GetSubscription() override{
			//Default behavior is to not filter messages
			return static_cast<unsigned>(EventCategory::WINDOW); // = 0xFFFFF...
		}

		bool Success = false;
	};

	struct DummyInputEvent : public Event {
		/**
		 * Virtual function to query type of Event object
		 */
		virtual utils::Name GetEventType() const {
			return "Dummy";
		};

		/**
		 * Virtual function to query category of Event object
		 */
		virtual EventCategory GetEventCategory() const {
			return EventCategory::INPUT;
		};

		/**
		 * Static function to get EventType info from C++ type info
		 */
		static utils::Name GetStaticEventType() {
			return "Dummy";
		}
	};

	TEST_CLASS(EventBusTests) {
	public:

		TEST_METHOD(RecieveMessageTest) {
			std::shared_ptr<EventBus> testBus = std::make_shared<EventBus>();
			TestEventBusNode testReceiver(testBus.get());
			testBus->PostEvent(new WindowClosedEvent());
			testBus->DispatchEvents();

			Assert::IsTrue(testReceiver.Success);
		}

		TEST_METHOD(IgnoreMessageTest) {
			std::shared_ptr<EventBus> testBus = std::make_shared<EventBus>();
			TestEventBusNode testReceiver(testBus.get());
		
			testBus->PostEvent(new DummyInputEvent());
			testBus->DispatchEvents();

			Assert::IsFalse(testReceiver.Success);
		}

	};

}