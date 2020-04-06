//STD Headers

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "core/gameplay_framework/Entity.h"
#include "core/input/components/InputComponent.h"
#include "core/rendering/components/GraphicsComponent.h"

using namespace core;

namespace EngineCoreTests {

	class ComponentA : public Component {
		TYPE_INFO_DECL(ComponentA)
	public:
		void Initialize() override {}
	};
	TYPE_INFO_IMPL(ComponentA)

	class ComponentB : public Component {
		TYPE_INFO_DECL(ComponentB)
		public:
			void Initialize() override {}
	};
	TYPE_INFO_IMPL(ComponentB)

	class ComponentA_Derived : public ComponentA {
		TYPE_INFO_DECL(ComponentA_Derived)
	public:
		void Initialize() override {}
	};
	TYPE_INFO_IMPL(ComponentA_Derived)

	TEST(TestEntities, AddGetTest) {
		Entity entity;
		auto compA = new ComponentA();
		auto compB = new ComponentB();

		entity.AddComponent(compA);
		entity.AddComponent(compB);

		ASSERT_NE(nullptr, entity.GetComponent<ComponentA>());
		ASSERT_EQ(compA, entity.GetComponent<ComponentA>());

		ASSERT_NE(nullptr, entity.GetComponent<ComponentB>());
		ASSERT_EQ(compB, entity.GetComponent<ComponentB>());
	}

	TEST(TestEntities, PolymorphicGetTest) {
		Entity entity;
		entity.AddComponent(new ComponentA_Derived());

		auto basePtr = entity.GetComponent<ComponentA>();
		ASSERT_NE(nullptr, basePtr);
	}

	TEST(TestEntities, GetComponentsTest) {
		Entity entity;
		entity.AddComponent(new ComponentA_Derived());
		entity.AddComponent(new ComponentA());
		entity.AddComponent(new ComponentB());
		
		ASSERT_EQ(2, entity.GetComponents<ComponentA>().size());
		ASSERT_EQ(1, entity.GetComponents<ComponentB>().size());
	}

}