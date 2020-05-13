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
		ENABLE_RTTI(ComponentA)
	public:
		void Initialize() override {}
	};

	class ComponentB : public Component {
		ENABLE_RTTI(ComponentB)
		public:
			void Initialize() override {}
	};

	class ComponentA_Derived : public ComponentA {
		ENABLE_RTTI(ComponentA_Derived)
	public:
		void Initialize() override {}
	};

	TEST(TestEntities, AddGetComponentTest) {
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

	TEST(TestEntities, PolymorphicGetComponentTest) {
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

	TEST(TestEntities, PositionTest) {
		auto parentHandle = std::make_unique<Entity>();
		Entity* parent = parentHandle.get();
		parent->SetPosition({ 5, 5, 5 });

		auto t1Handle = std::make_unique<Entity>();
		Entity* t1 = t1Handle.get();
		parent->AddChild(std::move(t1Handle));
		t1->SetLocalPosition({ 1, 0, 0 });

		//Test SetLocalPosition on leaf node
		t1->SetLocalPosition(t1->GetLocalPosition() + math::Vector3(1, 0, 0));
		ASSERT_EQ(math::Vector3(2, 0, 0), t1->GetLocalPosition());

		t1->SetPosition(math::Vector3(5, 5, 5));
		ASSERT_EQ(math::Vector3(0, 0, 0), t1->GetLocalPosition());
		ASSERT_EQ(math::Vector3(5, 5, 5), t1->GetPosition());

		parent->SetPosition({ 10, 10, 10 });
		ASSERT_EQ(math::Vector3(0, 0, 0), t1->GetLocalPosition());
		ASSERT_EQ(math::Vector3(10, 10, 10), t1->GetPosition());
		ASSERT_EQ(math::Vector3(10, 10, 10), parent->GetPosition());
		ASSERT_EQ(math::Vector3(10, 10, 10), parent->GetLocalPosition());
	}

	TEST(TestEntities, RotationTest) {
		auto parentHandle = std::make_unique<Entity>();
		Entity* parent = parentHandle.get();
		parent->SetPosition({ 0, 0, 3 });
		parent->SetRotation(math::Rotator(90, 0, 0));

		auto childHandle = std::make_unique<Entity>();
		Entity* child = childHandle.get();
		parent->AddChild(std::move(childHandle));
		child->SetLocalPosition({ 0, 0, 40 });

		ASSERT_EQ(math::Vector3(0, -40, 3), child->GetPosition());

		auto childLookDirection = child->GetForward().Normalize();
		auto translationVector = (parent->GetPosition() - child->GetPosition()).Normalize();

		ASSERT_EQ(childLookDirection, translationVector);
	}
}