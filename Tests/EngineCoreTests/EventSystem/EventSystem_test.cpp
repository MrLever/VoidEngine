//STD Headers
#include <memory>
#include <iostream>

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "core/event_system/EventSystem.h"

#include "core/event_system/Event.h"
#include "core/event_system/events/WindowClosedEvent.h"

using namespace core;

namespace EngineCoreTests {
	using namespace core;

	class DummyEventA : public Event {
		ENABLE_RTTI(DummyEventA);
	public:
	};

	class DummyEventB : public Event {
		ENABLE_RTTI(DummyEventB);
	public:
	};

	class DummyEventC : public Event {
		ENABLE_RTTI(DummyEventC);
	};

	TEST(EventSystemTests, SendMessageTest) {
		EventSystem system;

		EventListener listener1(&system);
		EventListener listener2(&system);

		bool event1Received = false;
		bool event2Received = false;
		bool event3Received = false;

		listener1.SubscribeToEvent<DummyEventA>(
			[&event1Received](auto event) {
				event1Received = true;
				ASSERT_EQ(DummyEventA::GetStaticTypename(), event->GetTypename());
			}
		);

		listener2.SubscribeToEvent<DummyEventB>(
			[&event2Received](auto event) {
				event2Received = true;
				ASSERT_EQ(DummyEventB::GetStaticTypename(), event->GetTypename());
			}
		);

		listener2.SubscribeToEvent<DummyEventC>(
			[&event3Received](auto event) {
				event3Received = true;
			}
		);

		listener2.PostEvent<DummyEventA>();
		listener1.PostEvent<DummyEventB>();

		system.DispatchEvents();

		ASSERT_EQ(true, event1Received);
		ASSERT_EQ(true, event2Received);
		ASSERT_EQ(false, event3Received);
	}

	TEST(EventSystemTests, DeregisterTest) {
		EventSystem system;

		EventListener listener1(&system);
		EventListener listener2(&system);
		
		bool eventAReceived = false;
		bool eventBReceived = false;
		bool eventCReceived = false;

		listener1.SubscribeToEvent<DummyEventA>(
			[&eventAReceived](auto event) {
				eventAReceived = true;
			}
		);

		listener1.SubscribeToEvent<DummyEventB>(
			[&eventBReceived](auto event) {
				eventBReceived = true;
			}
		);

		listener2.SubscribeToEvent<DummyEventC>(
			[&eventCReceived](auto event) {
				eventCReceived = true;
			}
		);

		//Ensure registration doesn't have any side effects
		ASSERT_EQ(false, eventAReceived);
		ASSERT_EQ(false, eventBReceived);
		ASSERT_EQ(false, eventCReceived);

		//Post an EventA
		listener2.PostEvent<DummyEventA>();
		system.DispatchEvents();

		//Assure it was received
		ASSERT_EQ(true, eventAReceived);
		eventAReceived = false;

		//Unsubscribe from EventA
		listener1.UnsubscribeFromEvent<DummyEventA>();

		//Post an EventA
		listener1.PostEvent<DummyEventA>();
		listener1.PostEvent<DummyEventB>();
		system.DispatchEvents();

		//Assert A is not received
		ASSERT_EQ(false, eventAReceived);

		//Assert someone else's registration not effected
		ASSERT_EQ(true, eventBReceived);
		eventBReceived = false;

		//Totally register listener 1
		listener1.SubscribeToEvent<DummyEventA>(
			[](auto event) {
				;
			}
		);
		
		listener1.SubscribeToEvent<DummyEventB>(
			[](auto event) {
				;
			}
		);

		listener1.SubscribeToEvent<DummyEventC>(
			[](auto event) {
				;
			}
		);

		//Totally deregister listener 1 from all events
		listener1.ClearSubscriptions();

		listener1.PostEvent<DummyEventC>();

		system.DispatchEvents();

		ASSERT_EQ(true, eventCReceived);
	}

}